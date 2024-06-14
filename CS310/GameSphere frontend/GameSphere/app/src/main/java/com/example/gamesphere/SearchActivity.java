package com.example.gamesphere;

import android.content.Intent;
import android.os.Bundle;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.EditText;
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

public class SearchActivity extends AppCompatActivity implements ReviewAdapter.OnReviewClickListener {

    private EditText searchEditText;
    private Button searchButton;
    private RecyclerView searchResultsList;
    private ReviewAdapter reviewAdapter;
    private List<Review> allReviews;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_search);

        searchEditText = findViewById(R.id.search_text);
        searchButton = findViewById(R.id.search_button);
        searchResultsList = findViewById(R.id.search_results_list);
        searchResultsList.setLayoutManager(new LinearLayoutManager(this));

        reviewAdapter = new ReviewAdapter(new ArrayList<>(), this);
        searchResultsList.setAdapter(reviewAdapter);

        allReviews = new ArrayList<>();

        searchButton.setOnClickListener(v -> {
            String query = searchEditText.getText().toString().trim();
            if (!query.isEmpty()) {
                filterReviews(query);
            } else {
                Toast.makeText(SearchActivity.this, "Please enter a search query", Toast.LENGTH_SHORT).show();
            }
        });

        loadReviews();
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == android.R.id.home) {
            finish();
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    private void loadReviews() {
        new Thread(() -> {
            try {
                URL url = new URL("http://10.0.2.2:8080/GameSphere/Profiles");
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

                JSONArray profilesArray = new JSONArray(content.toString());
                List<Review> reviews = new ArrayList<>();
                for (int i = 0; i < profilesArray.length(); i++) {
                    JSONObject profile = profilesArray.getJSONObject(i);
                    String reviewAuthor = profile.getString("nickName");
                    JSONArray gamesArray = profile.getJSONArray("games");
                    for (int j = 0; j < gamesArray.length(); j++) {
                        JSONObject game = gamesArray.getJSONObject(j);
                        Review review = new Review();
                        review.setReviewAuthor(reviewAuthor);
                        review.setGameName(game.getString("gameName"));
                        review.setReviewText(game.getString("review"));
                        review.setPlatform(new Gson().fromJson(game.getJSONObject("platform").toString(), Review.Platform.class));
                        review.setRatings(new Gson().fromJson(game.getJSONObject("ratings").toString(), Review.Ratings.class));
                        reviews.add(review);
                    }
                }
                allReviews = reviews;
                runOnUiThread(() -> reviewAdapter.updateReviews(allReviews));

            } catch (Exception e) {
                e.printStackTrace();
            }
        }).start();
    }

    private void filterReviews(String query) {
        List<Review> filteredReviews = new ArrayList<>();
        String lowerCaseQuery = query.toLowerCase().replaceAll("\\s+", "");

        for (Review review : allReviews) {
            String lowerCaseGameName = review.getGameName().toLowerCase().replaceAll("\\s+", "");
            if (lowerCaseGameName.contains(lowerCaseQuery)) {
                filteredReviews.add(review);
            }
        }

        reviewAdapter.updateReviews(filteredReviews);
    }

    @Override
    public void onReviewClick(Review review) {
        Intent intent = new Intent(SearchActivity.this, GameDetailActivity.class);
        intent.putExtra("reviewAuthor", review.getReviewAuthor());
        intent.putExtra("gameName", review.getGameName());
        intent.putExtra("reviewText", review.getReviewText());
        intent.putExtra("hoursPlayed", review.getHoursPlayed());
        intent.putExtra("ratings", new Gson().toJson(review.getRatings()));
        startActivity(intent);
    }
}
