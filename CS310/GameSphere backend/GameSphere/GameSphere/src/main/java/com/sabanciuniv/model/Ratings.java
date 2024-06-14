package com.sabanciuniv.model;

public class Ratings 
{
	private int Graphics;
	private int Gameplay;
	private int Story;
	private int Audio;
	private int Audience;
	private int Difficulty;
	private int Grind;
	private int GameTime;
	
	public Ratings() {
		// TODO Auto-generated constructor stub
	}
	
	public Ratings(int graphics, int gameplay, int story, int audio, int audience, int difficulty, int grind,
			int gameTime) {
		super();
		Graphics = graphics;
		Gameplay = gameplay;
		Story = story;
		Audio = audio;
		Audience = audience;
		Difficulty = difficulty;
		Grind = grind;
		GameTime = gameTime;
	}

	public int getGraphics() {
		return Graphics;
	}
	public void setGraphics(int graphics) {
		Graphics = graphics;
	}
	public int getGameplay() {
		return Gameplay;
	}
	public void setGameplay(int gameplay) {
		Gameplay = gameplay;
	}
	public int getStory() {
		return Story;
	}
	public void setStory(int story) {
		Story = story;
	}
	public int getAudio() {
		return Audio;
	}
	public void setAudio(int audio) {
		Audio = audio;
	}
	public int getAudience() {
		return Audience;
	}
	public void setAudience(int audience) {
		Audience = audience;
	}
	public int getDifficulty() {
		return Difficulty;
	}
	public void setDifficulty(int difficulty) {
		Difficulty = difficulty;
	}
	public int getGrind() {
		return Grind;
	}
	public void setGrind(int grind) {
		Grind = grind;
	}
	public int getGameTime() {
		return GameTime;
	}
	public void setGameTime(int gameTime) {
		GameTime = gameTime;
	}
	
	
	

}
