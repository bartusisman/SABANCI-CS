package com.example.gamesphere;

import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.google.gson.Gson;

public class GameDetailActivity extends AppCompatActivity {

    private TextView gameNameTextView;
    private TextView reviewAuthorTextView;
    private TextView reviewTextTextView;
    private TextView hoursPlayedTextView;
    private TextView ratingsTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game_detail);

        gameNameTextView = findViewById(R.id.game_name);
        reviewAuthorTextView = findViewById(R.id.review_author);
        reviewTextTextView = findViewById(R.id.review_text);
        hoursPlayedTextView = findViewById(R.id.hours_played);
        ratingsTextView = findViewById(R.id.ratings);

        Intent intent = getIntent();
        String gameName = intent.getStringExtra("gameName");
        String reviewAuthor = intent.getStringExtra("reviewAuthor");
        String reviewText = intent.getStringExtra("reviewText");
        String hoursPlayed = intent.getStringExtra("hoursPlayed");
        String ratingsJson = intent.getStringExtra("ratings");

        Review.Ratings ratings = new Gson().fromJson(ratingsJson, Review.Ratings.class);

        gameNameTextView.setText(gameName);
        reviewAuthorTextView.setText(reviewAuthor);
        reviewTextTextView.setText(reviewText);
        hoursPlayedTextView.setText(hoursPlayed);
        ratingsTextView.setText(
                "Graphics: " + ratings.getGraphics() + "\n" +
                        "Gameplay: " + ratings.getGameplay() + "\n" +
                        "Story: " + ratings.getStory() + "\n" +
                        "Audio: " + ratings.getAudio() + "\n" +
                        "Audience: " + ratings.getAudience() + "\n" +
                        "Difficulty: " + ratings.getDifficulty() + "\n" +
                        "Grind: " + ratings.getGrind() + "\n" +
                        "Game Time: " + ratings.getGameTime()
        );
    }
}
