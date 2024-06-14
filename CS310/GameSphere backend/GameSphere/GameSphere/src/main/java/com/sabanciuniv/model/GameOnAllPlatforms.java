package com.sabanciuniv.model;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

@Document
public class GameOnAllPlatforms {
	@Id String id;
	private String GameName;
	private String review;
	Platform platform;
	Ratings ratings;
	
	public GameOnAllPlatforms() {
		// TODO Auto-generated constructor stub
	}
	
	public GameOnAllPlatforms(String gameName, String review, Platform platform, Ratings ratings) {
		super();
		GameName = gameName;
		this.review = review;
		this.platform = platform;
		this.ratings = ratings;
	}

	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public String getGameName() {
		return GameName;
	}
	public void setGameName(String gameName) {
		GameName = gameName;
	}
	public String getReview() {
		return review;
	}
	public void setReview(String review) {
		this.review = review;
	}
	public Platform getPlatform() {
		return platform;
	}
	public void setPlatform(Platform platform) {
		this.platform = platform;
	}
	public Ratings getRatings() {
		return ratings;
	}
	public void setRatings(Ratings ratings) {
		this.ratings = ratings;
	}
	
	
	

}
