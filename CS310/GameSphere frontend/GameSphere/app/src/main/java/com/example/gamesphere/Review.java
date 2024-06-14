package com.example.gamesphere;

import com.google.gson.Gson;

public class Review {
    private String id;
    private String gameName;
    private String reviewText;
    private String reviewAuthor;
    private Platform platform;
    private Ratings ratings;

    // Getters and setters for id
    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    // Getters and setters for gameName
    public String getGameName() {
        return gameName;
    }

    public void setGameName(String gameName) {
        this.gameName = gameName;
    }

    // Getters and setters for reviewText
    public String getReviewText() {
        return reviewText;
    }

    public void setReviewText(String reviewText) {
        this.reviewText = reviewText;
    }

    // Getters and setters for reviewAuthor
    public String getReviewAuthor() {
        return reviewAuthor;
    }

    public void setReviewAuthor(String reviewAuthor) {
        this.reviewAuthor = reviewAuthor;
    }

    // Getters and setters for platform
    public Platform getPlatform() {
        return platform;
    }

    public void setPlatform(Platform platform) {
        this.platform = platform;
    }

    // Getters and setters for ratings
    public Ratings getRatings() {
        return ratings;
    }


    public void setRatings(Ratings ratings) {
        this.ratings = ratings;
    }

    // Set hours played
    public void setHoursPlayed(String hoursPlayed) {
        this.platform = new Gson().fromJson(hoursPlayed, Platform.class);
    }

    public int getHoursPlayed() {
        return platform.getHoursPlayed();
    }


    public static class Platform {
        private int steamHours;
        private int psnHours;
        private int xboxHours;
        private int epicgamesHours;

        // Getters and setters for steamHours
        public int getSteamHours() {
            return steamHours;
        }

        public void setSteamHours(int steamHours) {
            this.steamHours = steamHours;
        }

        // Getters and setters for psnHours
        public int getPsnHours() {
            return psnHours;
        }

        public void setPsnHours(int psnHours) {
            this.psnHours = psnHours;
        }

        // Getters and setters for xboxHours
        public int getXboxHours() {
            return xboxHours;
        }

        public void setXboxHours(int xboxHours) {
            this.xboxHours = xboxHours;
        }

        // Getters and setters for epicgamesHours
        public int getEpicgamesHours() {
            return epicgamesHours;
        }

        public void setEpicgamesHours(int epicgamesHours) {
            this.epicgamesHours = epicgamesHours;
        }

        public int getHoursPlayed()
        {
            return steamHours + psnHours + xboxHours + epicgamesHours;
        }


    }

    public static class Ratings {
        private int graphics;
        private int gameplay;
        private int story;
        private int audio;
        private int audience;
        private int difficulty;
        private int grind;
        private int gameTime;

        // Getters and setters for graphics
        public int getGraphics() {
            return graphics;
        }

        public void setGraphics(int graphics) {
            this.graphics = graphics;
        }

        // Getters and setters for gameplay
        public int getGameplay() {
            return gameplay;
        }

        public void setGameplay(int gameplay) {
            this.gameplay = gameplay;
        }

        // Getters and setters for story
        public int getStory() {
            return story;
        }

        public void setStory(int story) {
            this.story = story;
        }

        // Getters and setters for audio
        public int getAudio() {
            return audio;
        }

        public void setAudio(int audio) {
            this.audio = audio;
        }

        // Getters and setters for audience
        public int getAudience() {
            return audience;
        }

        public void setAudience(int audience) {
            this.audience = audience;
        }

        // Getters and setters for difficulty
        public int getDifficulty() {
            return difficulty;
        }

        public void setDifficulty(int difficulty) {
            this.difficulty = difficulty;
        }

        // Getters and setters for grind
        public int getGrind() {
            return grind;
        }

        public void setGrind(int grind) {
            this.grind = grind;
        }

        // Getters and setters for gameTime
        public int getGameTime() {
            return gameTime;
        }

        public void setGameTime(int gameTime) {
            this.gameTime = gameTime;
        }
    }
}
