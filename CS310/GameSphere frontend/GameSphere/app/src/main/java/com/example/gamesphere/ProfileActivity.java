package com.example.gamesphere;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.google.gson.Gson;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;

public class ProfileActivity extends AppCompatActivity implements ReviewAdapter.OnReviewClickListener {

    private RecyclerView reviewList;
    private ReviewAdapter reviewAdapter;
    private List<Review> reviews;
    private Button postButton;

    private static final int REQUEST_CODE_POST_REVIEW = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_profile);

        reviewList = findViewById(R.id.profile_review_list);
        reviewList.setLayoutManager(new LinearLayoutManager(this));

        reviews = new ArrayList<>();
        reviewAdapter = new ReviewAdapter(reviews, this);
        reviewList.setAdapter(reviewAdapter);

        postButton = findViewById(R.id.post_button);
        postButton.setOnClickListener(v -> {
            Intent intent = new Intent(ProfileActivity.this, PostActivity.class);
            startActivityForResult(intent, REQUEST_CODE_POST_REVIEW);
        });

        loadUserReviews();
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == android.R.id.home) {
            finish();
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    private void loadUserReviews() {
        new Thread(() -> {
            try {
                String profileId = getUserProfileId();
                if (profileId.isEmpty()) {
                    runOnUiThread(() -> Toast.makeText(ProfileActivity.this, "User profile not found", Toast.LENGTH_SHORT).show());
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
                reviews.clear();
                for (int i = 0; i < gamesArray.length(); i++) {
                    JSONObject game = gamesArray.getJSONObject(i);
                    Review review = new Review();
                    review.setReviewAuthor(profile.getString("nickName"));
                    review.setGameName(game.getString("gameName"));
                    review.setReviewText(game.getString("review"));
                    review.setPlatform(new Gson().fromJson(game.getJSONObject("platform").toString(), Review.Platform.class));
                    review.setRatings(new Gson().fromJson(game.getJSONObject("ratings").toString(), Review.Ratings.class));
                    reviews.add(review);
                }

                runOnUiThread(() -> reviewAdapter.notifyDataSetChanged());

            } catch (Exception e) {
                e.printStackTrace();
            }
        }).start();
    }

    private String getUserProfileId() {
        SharedPreferences sharedPreferences = getSharedPreferences("user_prefs", MODE_PRIVATE);
        return sharedPreferences.getString("profile_id", "");
    }

    @Override
    public void onReviewClick(Review review) {
        // Handle review click if needed
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQUEST_CODE_POST_REVIEW && resultCode == RESULT_OK) {
            loadUserReviews();
        }
    }
}
