import java.util.ArrayList;
import java.util.Random;

public class Algorithm 
{
    private String namePlayerOne;			
    private String namePlayerTwo;		
    private int mode;					
    private int turn;
    
    /**Array delle mosse che fa il primo giocatore*/
    private ArrayList<Integer> movesPOne;
    /**Array delle mosse che fa il secondo giocatore*/
    private ArrayList<Integer> movesPTwo;
    private int[] positionWin; 
    
	private boolean won;
	private boolean enemyWon;
	private boolean tie;
	private boolean startX;
	
    public Algorithm(String namePlayerOne, String namePlayerTwo, int mode) 
    {
		this.namePlayerOne = namePlayerOne;
		this.namePlayerTwo = namePlayerTwo;
		this.mode 		   = mode;
		this.turn		   = 0;
		this.movesPOne     = new ArrayList<Integer>();
        this.movesPTwo     = new ArrayList<Integer>();
		this.won           = false;
		this.enemyWon      = false;
		this.tie           = false;
		this.startX        = true;
		this.positionWin   = new int[3];
	}

	public String getNamePlayerOne() 
	{
		return namePlayerOne;
	}
	
	public void setNamePlayerTwo(String name)
	{
		this.namePlayerTwo = name;
	}
	
	public String getNamePlayerTwo() 
	{
		return namePlayerTwo;
	}

	public int getMode() 
	{
		return mode;
	}
	
	public void setTurnClient()
	{
		this.turn   = 1;
		this.startX = false;
	}
	
	public int getTurn() 
	{
		return turn;
	}		
	
	public boolean isWon() 
	{
		return won;
	}

	public boolean isEnemyWon()
	{
		return enemyWon;
	}
	
	public boolean isTie()
	{
		return tie;
	}
	
	public boolean isMovePossible(int pressed)
	{
		if(movesPOne.contains(pressed) || movesPTwo.contains(pressed))
			return false;
		return true;
	}
	
	public boolean canContinue()
	{
		if(isWon() || isEnemyWon() || isTie())
			return false;
		return true;
	}
	
	public int[] positionsWin()
	{
		return positionWin;
	}
	
    /**
    *Avvio dell'algoritmo della modalita Player vs Player in cui si effettua semplicemente il turno
    *@param pressed corrisponde al bottone premuto sul layout
    */
    public void algorithmPlayer(int pressed)
    {
    	if(turn%2 == 0)
    	{
    		movesPOne.add(pressed);
    		won = calcWin(movesPOne);
    	}
    	else if(turn%2 == 1 && this.canContinue())
    	{
    		movesPTwo.add(pressed);
    		enemyWon = calcWin(movesPTwo);
    	}
    	turn++;
    	controlTie();
    }
    
    private void controlTie()
    {
    	if(turn == 9 && !won && !enemyWon && startX)
    		tie = true;
    	
    	if(turn == 10 && !won && !enemyWon && !startX)
    		tie = true;
    }
    
	private boolean calcWin(ArrayList<Integer> movesPlayer) 
	{
		boolean result = false;
		
		for(int i = 0; i < Constants.WINS.length; i++)
			if(searchWin(movesPlayer, Constants.WINS[i]))
			{
				result = true;
				positionWin = Constants.WINS[i];
			}
		return result;
	}
	
	private boolean searchWin(ArrayList<Integer> movesPlayer, int search[])
	{		
		for(int i = 0; i < search.length; i++)
			if(!movesPlayer.contains(search[i]))
				return false;
		return true;
	}
	
	
    public int IA(int pressed)
    {
    	//CONTROLLLO ATTACCO
    	int attach = attachOrDefend(movesPTwo, movesPOne);
    	if(attach > Constants.ERROR)
    		return attach;
    	
    	//PRIMA MOSSA 
    	if(pressed == Constants.CENTER && movesPOne.size() == 1)
    		return extractFromArray(Constants.EDGE);
    	if(searchInArray(Constants.EDGE, pressed) && movesPOne.size() == 1)
    		return Constants.CENTER;
    	if(searchInArray(Constants.SIDE, pressed) && movesPOne.size() == 1)
    		return extractFromArray(Constants.EDGENEAR[pressed]);
    	
    	//CONTROLLO DIFESA
    	int defend = attachOrDefend(movesPOne, movesPTwo);
    	if(defend > Constants.ERROR)
    		return defend;
    		
    	//CONTROLLI SPECIALI 
    	if(movesPOne.size() > 2)
    		return extractFromArray(Constants.SIDE);
    	
    	for(int i = 0; i < Constants.SIDE.length; i++)
    		if(movesPOne.get(0) == Constants.SIDE[i] && movesPOne.size() == 2)
    			return Constants.CENTER;
    	
    	if(searchInArray(Constants.EDGE, movesPOne.get(0)) && searchInArray(Constants.EDGE, movesPOne.get(1)))
    		return extractFromArray(Constants.SIDE);
    	
    	if(movesPOne.get(0) == Constants.CENTER && searchInArray(Constants.EDGE, movesPOne.get(1)))
    		return extractFromArray(Constants.EDGE);
    	
    	if(searchInArray(Constants.EDGE, movesPOne.get(0)) && searchInArray(Constants.SIDE, movesPOne.get(1)))
    		return extractFromArray(Constants.EDGE); 
    	
    	return Constants.ERROR;
	}
	
    private int attachOrDefend(ArrayList<Integer> movesPlayer, ArrayList<Integer> movesPlayerControl)
    {
    	for(int i = 0; i < 9; i++)
    	{
    		movesPlayer.add(i);
    		if(calcWin(movesPlayer) && !movesPlayerControl.contains(i))
    		{
    			movesPlayer.remove(movesPlayer.size() - 1);
    			return i;
    		}
    		movesPlayer.remove(movesPlayer.size() - 1);
    	}
    	return Constants.ERROR;
    }
    
	private int extractFromArray(int array[])
	{
		Random random = new Random();
		int number = -1;
		for(int i = 0; i < 200; i++)
		{
			number = random.nextInt(array.length);
			System.out.println(array[number]);
			if(!movesPOne.contains(array[number]) && !movesPTwo.contains(array[number]))
				return array[number];	
		}
		return Constants.ERROR;
	}
	
	private boolean searchInArray(int array[], int number)
	{
		for(int i = 0; i < array.length; i++)
			if(array[i] == number)
				return true;
		return false;
	}
	
	
	
	
    public void resetGame()
    {
    	movesPOne.clear();
    	movesPTwo.clear();
    	won      = false;
    	enemyWon = false;
    	tie      = false;
    	resetTurn();
    }
    
    private void resetTurn()
    {
    	if(turn%2 == 0 || mode == 1)
    	{
    		turn   = 0;
    		startX = true;
    	}
		else
		{
    		turn 	= 1;
    		startX  = false;
		}
    }   
}
