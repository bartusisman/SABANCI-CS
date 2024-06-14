package com.example.gamesphere;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class AuthActivity extends AppCompatActivity {
    private static final String TAG = "AuthActivity";
    private EditText usernameEditText;
    private EditText passwordEditText;
    private Button loginButton;
    private Button registerButton;
    private ExecutorService executorService;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_auth);

        usernameEditText = findViewById(R.id.username);
        passwordEditText = findViewById(R.id.passoword);
        loginButton = findViewById(R.id.login_button);
        registerButton = findViewById(R.id.register_button);
        executorService = Executors.newFixedThreadPool(2);

        loginButton.setOnClickListener(v -> {
            String username = usernameEditText.getText().toString();
            String password = passwordEditText.getText().toString();
            executorService.execute(() -> {
                boolean result = login(username, password);
                runOnUiThread(() -> {
                    if (result) {
                        Toast.makeText(AuthActivity.this, "Login successful", Toast.LENGTH_SHORT).show();
                        Intent intent = new Intent(AuthActivity.this, MainActivity.class);
                        startActivity(intent);
                        finish();
                    } else {
                        Toast.makeText(AuthActivity.this, "Invalid credentials", Toast.LENGTH_SHORT).show();
                    }
                });
            });
        });

        registerButton.setOnClickListener(v -> {
            String username = usernameEditText.getText().toString();
            String password = passwordEditText.getText().toString();
            executorService.execute(() -> {
                boolean result = register(username, password);
                runOnUiThread(() -> {
                    if (result) {
                        Toast.makeText(AuthActivity.this, "Registration successful", Toast.LENGTH_SHORT).show();
                    } else {
                        Toast.makeText(AuthActivity.this, "Registration failed", Toast.LENGTH_SHORT).show();
                    }
                });
            });
        });
    }

    private void saveUserProfileId(String profileId) {
        SharedPreferences sharedPreferences = getSharedPreferences("user_prefs", MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPreferences.edit();
        editor.putString("profile_id", profileId);
        editor.apply();
    }

    private boolean login(String username, String password) {
        try {
            URL url = new URL("http://10.0.2.2:8080/GameSphere/Credentials");
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("GET");

            BufferedReader in = new BufferedReader(new InputStreamReader(conn.getInputStream()));
            StringBuilder content = new StringBuilder();
            String inputLine;
            while ((inputLine = in.readLine()) != null) {
                content.append(inputLine);
            }
            in.close();
            conn.disconnect();

            JSONArray credentialsArray = new JSONArray(content.toString());
            for (int i = 0; i < credentialsArray.length(); i++) {
                JSONObject credential = credentialsArray.getJSONObject(i);
                if (credential.getString("userName").equals(username) &&
                        credential.getString("passoword").equals(password)) {
                    String profileId = getProfileIdByUsername(username);
                    if (profileId != null) {
                        saveUserProfileId(profileId);
                        return true;
                    }
                }
            }
        } catch (Exception e) {
            Log.e(TAG, "Error during login", e);
        }
        return false;
    }

    private String getProfileIdByUsername(String username) {
        try {
            URL url = new URL("http://10.0.2.2:8080/GameSphere/Users");
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("GET");

            BufferedReader in = new BufferedReader(new InputStreamReader(conn.getInputStream()));
            StringBuilder content = new StringBuilder();
            String inputLine;
            while ((inputLine = in.readLine()) != null) {
                content.append(inputLine);
            }
            in.close();
            conn.disconnect();

            JSONArray usersArray = new JSONArray(content.toString());
            Log.d(TAG, "Fetched users: " + usersArray.toString());

            for (int i = 0; i < usersArray.length(); i++) {
                JSONObject user = usersArray.getJSONObject(i);
                JSONObject credentials = user.getJSONObject("credentials");
                Log.d(TAG, "Checking user: " + credentials.getString("userName"));

                if (credentials.getString("userName").equals(username)) {
                    Log.d(TAG, "Username match found: " + username);
                    JSONObject profile = user.getJSONObject("profile");
                    String profileId = profile.getString("id");
                    Log.d(TAG, "Found profile ID: " + profileId);
                    return profileId;
                }
            }
        } catch (Exception e) {
            Log.e(TAG, "Error fetching profile ID", e);
        }
        return null;
    }

    private boolean register(String username, String password) {
        try {
            // Create credentials
            URL credentialsUrl = new URL("http://10.0.2.2:8080/GameSphere/Credentials/save");
            HttpURLConnection credentialsConn = (HttpURLConnection) credentialsUrl.openConnection();
            credentialsConn.setRequestMethod("POST");
            credentialsConn.setRequestProperty("Content-Type", "application/json");
            credentialsConn.setDoOutput(true);

            JSONObject credential = new JSONObject();
            credential.put("userName", username);
            credential.put("passoword", password);

            OutputStream os = credentialsConn.getOutputStream();
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(os, StandardCharsets.UTF_8));
            writer.write(credential.toString());
            writer.flush();
            writer.close();
            os.close();

            int credentialsResponseCode = credentialsConn.getResponseCode();
            if (credentialsResponseCode != 200) {
                credentialsConn.disconnect();
                return false;
            }

            // Read created credential
            BufferedReader credentialsReader = new BufferedReader(new InputStreamReader(credentialsConn.getInputStream()));
            StringBuilder credentialsContent = new StringBuilder();
            String credentialsLine;
            while ((credentialsLine = credentialsReader.readLine()) != null) {
                credentialsContent.append(credentialsLine);
            }
            credentialsReader.close();
            credentialsConn.disconnect();

            JSONObject savedCredential = new JSONObject(credentialsContent.toString());
            String credentialId = savedCredential.getString("id");

            // Create profile
            URL profileUrl = new URL("http://10.0.2.2:8080/GameSphere/Profile/save");
            HttpURLConnection profileConn = (HttpURLConnection) profileUrl.openConnection();
            profileConn.setRequestMethod("POST");
            profileConn.setRequestProperty("Content-Type", "application/json");
            profileConn.setDoOutput(true);

            JSONObject profile = new JSONObject();
            profile.put("nickName", username);
            profile.put("followerCount", 0);
            profile.put("followingCount", 0);
            profile.put("gamesId", new JSONArray());

            os = profileConn.getOutputStream();
            writer = new BufferedWriter(new OutputStreamWriter(os, StandardCharsets.UTF_8));
            writer.write(profile.toString());
            writer.flush();
            writer.close();
            os.close();

            int profileResponseCode = profileConn.getResponseCode();

            // Read profile response
            InputStream profileInputStream = profileResponseCode == 200 ? profileConn.getInputStream() : profileConn.getErrorStream();
            BufferedReader profileReader = new BufferedReader(new InputStreamReader(profileInputStream));
            StringBuilder profileContent = new StringBuilder();
            String profileLine;
            while ((profileLine = profileReader.readLine()) != null) {
                profileContent.append(profileLine);
            }
            profileReader.close();
            profileConn.disconnect();

            if (profileResponseCode != 200) {
                return false;
            }

            JSONObject savedProfile = new JSONObject(profileContent.toString());
            String profileId = savedProfile.getString("id");
            saveUserProfileId(profileId);

            // Create user linking credentials and profile
            URL userUrl = new URL("http://10.0.2.2:8080/GameSphere/Users/save");
            HttpURLConnection userConn = (HttpURLConnection) userUrl.openConnection();
            userConn.setRequestMethod("POST");
            userConn.setRequestProperty("Content-Type", "application/json");
            userConn.setDoOutput(true);

            JSONObject user = new JSONObject();
            user.put("profileId", profileId);
            user.put("credentialsId", credentialId);

            os = userConn.getOutputStream();
            writer = new BufferedWriter(new OutputStreamWriter(os, StandardCharsets.UTF_8));
            writer.write(user.toString());
            writer.flush();
            writer.close();
            os.close();

            int userResponseCode = userConn.getResponseCode();
            userConn.disconnect();

            return userResponseCode == 200;
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }




}
