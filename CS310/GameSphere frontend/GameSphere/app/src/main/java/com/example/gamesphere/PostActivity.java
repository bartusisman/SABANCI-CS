package com.example.gamesphere;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;
import java.nio.charset.StandardCharsets;

public class PostActivity extends AppCompatActivity {

    private EditText gameNameEditText;
    private EditText reviewEditText;
    private Button submitButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_post);

        gameNameEditText = findViewById(R.id.game_name);
        reviewEditText = findViewById(R.id.review_text);
        submitButton = findViewById(R.id.submit_button);

        submitButton.setOnClickListener(v -> {
            String gameName = gameNameEditText.getText().toString();
            String review = reviewEditText.getText().toString();
            if (!gameName.isEmpty() && !review.isEmpty()) {
                postReview(gameName, review);
            } else {
                Toast.makeText(PostActivity.this, "Please enter a game name and review", Toast.LENGTH_SHORT).show();
            }
        });
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == android.R.id.home) {
            finish();
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    private String getUserProfileId() {
        SharedPreferences sharedPreferences = getSharedPreferences("user_prefs", MODE_PRIVATE);
        return sharedPreferences.getString("profile_id", "");
    }

    private void postReview(String gameName, String review) {
        new Thread(() -> {
            try {
                String profileId = getUserProfileId();
                if (profileId.isEmpty()) {
                    runOnUiThread(() -> Toast.makeText(PostActivity.this, "User profile not found", Toast.LENGTH_SHORT).show());
                    return;
                }

                URL url = new URL("http://10.0.2.2:8080/GameSphere/Profiles/" + profileId);
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

                JSONObject profile = new JSONObject(content.toString());
                JSONArray gamesArray = profile.getJSONArray("games");

                JSONObject newGame = new JSONObject();
                newGame.put("gameName", gameName);
                newGame.put("review", review);
                // Add more fields like platform and ratings if needed
                gamesArray.put(newGame);

                profile.put("games", gamesArray);

                // Update the profile
                URL updateUrl = new URL("http://10.0.2.2:8080/GameSphere/Profiles/save");
                HttpURLConnection updateConn = (HttpURLConnection) updateUrl.openConnection();
                updateConn.setRequestMethod("POST");
                updateConn.setRequestProperty("Content-Type", "application/json");
                updateConn.setDoOutput(true);

                OutputStream os = updateConn.getOutputStream();
                BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(os, StandardCharsets.UTF_8));
                writer.write(profile.toString());
                writer.flush();
                writer.close();
                os.close();

                int responseCode = updateConn.getResponseCode();
                updateConn.disconnect();

                runOnUiThread(() -> {
                    if (responseCode == 200) {
                        Toast.makeText(PostActivity.this, "Review posted successfully", Toast.LENGTH_SHORT).show();
                        setResult(RESULT_OK);
                        finish();
                    } else {
                        Toast.makeText(PostActivity.this, "Failed to post review", Toast.LENGTH_SHORT).show();
                    }
                });
            } catch (Exception e) {
                e.printStackTrace();
            }
        }).start();
    }
}
