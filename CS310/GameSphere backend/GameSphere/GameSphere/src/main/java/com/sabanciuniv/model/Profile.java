package com.sabanciuniv.model;

import java.util.List;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.DBRef;
import org.springframework.data.mongodb.core.mapping.Document;

@Document
public class Profile {
	@Id String id;
	private int followerCount;
	private int followingCount;
	private String nickName;
	@DBRef List<GameOnAllPlatforms> Games;
	
	public Profile() {
		// TODO Auto-generated constructor stub
	}
	
	public Profile(int followerCount, int followingCount, List<GameOnAllPlatforms> games, String nickName) {
		super();
		this.followerCount = followerCount;
		this.followingCount = followingCount;
		Games = games;
		this.nickName = nickName;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public int getFollowerCount() {
		return followerCount;
	}

	public void setFollowerCount(int followerCount) {
		this.followerCount = followerCount;
	}

	public int getFollowingCount() {
		return followingCount;
	}

	public void setFollowingCount(int followingCount) {
		this.followingCount = followingCount;
	}

	public List<GameOnAllPlatforms> getGames() {
		return Games;
	}

	public void setGames(List<GameOnAllPlatforms> games) {
		Games = games;
	}

	public String getNickName() {
		return nickName;
	}

	public void setNickName(String nickName) {
		this.nickName = nickName;
	}
	
	
	
	
	
}
