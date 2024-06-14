package com.sabanciuniv.model;

import java.util.List;

public class ProfilePayload {
	private int followerCount;
	private int followingCount;
	private String nickName;
	private List<String> GamesId;
	
	public ProfilePayload() {
		// TODO Auto-generated constructor stub
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

	public String getNickName() {
		return nickName;
	}

	public void setNickName(String nickName) {
		this.nickName = nickName;
	}

	public List<String> getGamesId() {
		return GamesId;
	}

	public void setGamesId(List<String> gamesId) {
		GamesId = gamesId;
	}

	
}
