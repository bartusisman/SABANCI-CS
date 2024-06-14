package com.sabanciuniv.model;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.DBRef;
import org.springframework.data.mongodb.core.mapping.Document;

@Document
public class User {
	@Id private String id;
	@DBRef Profile profile;
	@DBRef Credentials credentials;
	
	public User() {
		// TODO Auto-generated constructor stub
	}
	
	

	public User(Profile profile, Credentials credentials) {
		super();
		this.profile = profile;
		this.credentials = credentials;
	}



	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public Profile getProfile() {
		return profile;
	}

	public void setProfile(Profile profile) {
		this.profile = profile;
	}

	public Credentials getCredentials() {
		return credentials;
	}

	public void setCredentials(Credentials credentials) {
		this.credentials = credentials;
	}
	
	
	

}
