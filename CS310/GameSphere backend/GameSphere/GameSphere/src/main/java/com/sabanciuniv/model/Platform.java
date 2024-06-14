package com.sabanciuniv.model;

public class Platform 
{
	private int steamHours;
	private int psnHours;
	private int xboxHours;
	private int epicgamesHours;
	
	public Platform() 
	{
		steamHours=0;
		psnHours=0;
		xboxHours=0;
		epicgamesHours=0;
	}
	
	public Platform(int steamHours, int psnHours, int xboxHours, int epicgamesHours) {
		super();
		this.steamHours = steamHours;
		this.psnHours = psnHours;
		this.xboxHours = xboxHours;
		this.epicgamesHours = epicgamesHours;
	}
	
	public int getSteamHours() {
		return steamHours;
	}
	public void setSteamHours(int steamHours) {
		this.steamHours = steamHours;
	}
	public int getPsnHours() {
		return psnHours;
	}
	public void setPsnHours(int psnHours) {
		this.psnHours = psnHours;
	}
	public int getXboxHours() {
		return xboxHours;
	}
	public void setXboxHours(int xboxHours) {
		this.xboxHours = xboxHours;
	}
	public int getEpicgamesHours() {
		return epicgamesHours;
	}
	public void setEpicgamesHours(int epicgamesHours) {
		this.epicgamesHours = epicgamesHours;
	}
	
	

}
