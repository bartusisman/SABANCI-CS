package com.sabanciuniv.model;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

@Document
public class Credentials {
	@Id String id;
	private String userName;
	private String password;
	
	public Credentials() {
		// TODO Auto-generated constructor stub
	}
		
	public Credentials(String userName, String passoword) {
		super();
		this.userName = userName;
		this.password = passoword;
	}

	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public String getUserName() {
		return userName;
	}
	public void setUserName(String userName) {
		this.userName = userName;
	}
	public String getPassoword() {
		return password;
	}
	public void setPassoword(String passoword) {
		this.password = passoword;
	}
	
	
}
