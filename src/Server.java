import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class Server implements Runnable
{
	private String  ip;
	private int     nPort;
	private int     errors;	
	private boolean yourTurn = false;
	private boolean circle = true;
	private boolean accepted = false;
	private boolean connInterrupt = false;
	
	private ServerSocket   server;
	private Socket         clientSocket;
	private Socket         serverSocket;
	private BufferedReader buffReader;
	private BufferedWriter buffWriter;
	private GameController controller; 
	private Thread         thread;
	
	public Server(String ip, int nPort, GameController controller)
	{
		this.ip            = ip;
		this.nPort         = nPort;
		this.controller    = controller;
		this.errors        = 0;
		this.yourTurn      = false;
		this.circle        = true;
		this.accepted      = false;
		this.connInterrupt = false;
		this.server        = null;
		this.clientSocket  = null;
		this.serverSocket  = null;
		
		if (!connect()) 
			initializeServer();
		
		thread = new Thread(this, "LAN");
		thread.start();
	}

	public void run() 
	{
		while(true) 
		{
			tick();
			if(!circle && !accepted && !connInterrupt) 
				listenForServerRequest();
		}
	}
	
	private void tick() 
	{
		if(errors >= 10) 
			connInterrupt = true;

		int numPressed = -1;
		try 
		{
			if(this.accepted)
				numPressed = buffReader.read();
		} 
		catch(Exception e) 
		{	
			e.printStackTrace();
			errors++;
		}
		
		if(!yourTurn && !connInterrupt && numPressed >= 0 && numPressed < 9 && numPressed != -1) //MOssa giocatore 
		{
			controller.lanMoves(numPressed);
			yourTurn = true;
		}
		else if(numPressed >= 32 && numPressed <= 126 || numPressed == 10)
			controller.readMessage((char)numPressed);
	}
	
	///LO FA IL CLIENT-----------------------------------------------------------------
	private boolean connect() 
	{
		try {
			clientSocket           = new Socket(ip, nPort);
		    OutputStream os        = clientSocket.getOutputStream();
		    OutputStreamWriter osw = new OutputStreamWriter(os);
		    buffWriter             = new BufferedWriter(osw);
			
			InputStream is         = clientSocket.getInputStream();
		    InputStreamReader isr  = new InputStreamReader(is);
		    buffReader             = new BufferedReader(isr);
		    
		    controller.graphicClient();
			accepted = true;
		}
		catch(Exception e) 
		{
			//IMPOSSIBILE CONNETTERSI QUINDI APRIRO' IL SERVER
			return false;
		}
		//CONNESSIONE RIUSCITA QUINDI NON C'E' BISOGNO DI APRIRE UN SERVER
		return true;
	}
	
	///LO FA IL SERVER-----------------------------------------------------------------
	private void listenForServerRequest() 
	{
		try 
		{
			serverSocket           = server.accept();
		    OutputStream os        = serverSocket.getOutputStream();
		    OutputStreamWriter osw = new OutputStreamWriter(os);
		    buffWriter             = new BufferedWriter(osw);
			
			InputStream is         = serverSocket.getInputStream();
		    InputStreamReader isr  = new InputStreamReader(is);
		    buffReader  		   = new BufferedReader(isr);
		    
			accepted = true;
		}
		catch(Exception e) 
		{
			e.printStackTrace();
		}
	}
	
	///LO FA IL SERVER-----------------------------------------------------------------
	private void initializeServer() 
	{
		try 
		{
			server = new ServerSocket(nPort, 2, InetAddress.getByName(ip));
		} 
		catch(Exception e)
		{
			e.printStackTrace();
		}
		yourTurn 	   = true;
		circle		   = false;
	}
	
	public void sendNumPressed(int numPressed)
	{
		try 
		{
			buffWriter.write(numPressed);
			buffWriter.flush();
		} 
		catch(Exception e1) 
		{
			errors++;
			e1.printStackTrace();
		}
	}
	
	public void sendMessage(String message)
	{	
		try 
		{
			buffWriter.write(message);
			buffWriter.flush();
		} 
		catch(Exception e1) 
		{
			errors++;
			e1.printStackTrace();
		}
	}
	
	public void setYourTurn(boolean state)
	{
		this.yourTurn = state;
	}
	
	public boolean getYourTurn()
	{
		return this.yourTurn;
	}
	
	public boolean getUnableConn()
	{
		return this.connInterrupt;
	}
	
	public boolean getAccepted()
	{
		return this.accepted;
	}
	
	public void exit() 
	{
		try 
		{
			this.connInterrupt = true;
			this.accepted      = false;
			this.thread.interrupt();

			if(this.serverSocket != null)
				this.serverSocket.close();
			if(this.server != null)
				this.server.close();	
			if(this.clientSocket != null)
				this.clientSocket.close();
			
			   this.buffReader.close();
			   this.buffWriter.close();
		} 
		catch(Exception e) 
		{
			e.printStackTrace();
		}
	}
}
