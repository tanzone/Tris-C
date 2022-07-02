/**
 * @(#)Stats.java
 *
 * Classe dedicata alla gestione delle statistiche di gioco
 * @author Tanzi Manuel
 * @version 1.00 13/09/2018
 */

public class Stats 
{
	private int gamePlayed;
	private int winPlayerOne;
	private int winPlayerTwo;
	
	public Stats()
	{
		gamePlayed   = 0;
		winPlayerOne = 0;
		winPlayerTwo = 0;
	}
	
	public void addGamePlayed()
	{
		gamePlayed++;
	}

	public void addWinPlayerOne() 
	{
		winPlayerOne++;
	}

	public void addWinPlayerTwo()
	{
		winPlayerTwo++;
	}	

	public String getGamePlayed()
	{
		return ": " + gamePlayed;
	}

	public String getWinPlayerOne() 
	{
		return ": " + winPlayerOne;
	}

	public String getWinPlayerTwo() 
	{
		return ": " + winPlayerTwo;
	}

	public String getDraw() 
	{
		int num = this.gamePlayed - (this.winPlayerOne + this.winPlayerTwo);
		
		return ": " + num;
	}

	public String getPercent() 
	{		
		return ": " + calcPercent() + " %";
	}
	
	private String calcPercent()
	{
		float number = ((float)winPlayerOne / (float)gamePlayed) * 100;
				
		return String.format ("%.2f", number);
	}
}
