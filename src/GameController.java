/**
 * @(#)GameController.java
 *
 * Controller del file FXML game.fxml
 * @author Tanzi Manuel
 * @version 1.00 13/09/2018
 */

import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

public class GameController implements Initializable
{
	/*AnchorPane principale che racchiude tutto al suo interno*/
	@FXML
    private AnchorPane parentGame;			
	/*textArea della chat dei messaggi*/
	@FXML
    public TextArea textArea;		
	/*textField in cui scriviamo il messaggio da inviare*/
	@FXML
    private TextField message;
    /*bottone che invia il messagio*/
    @FXML
    private Button btnSend;		
	/*Lista di bottoni posti sopra al gioco che caratterizzano le varie categorie*/
	@FXML
    private List<Button> buttonSettings; 
    /*Lista dei bottoni che identificano il campo da gioco*/
	@FXML
    private List<Button> buttonPlay;
    /*Lista di immagini che vengono settate nella barra del menu in alto*/
	@FXML
    private List<ImageView> imageSettings; 
    /*Lista di immagini che devono essere messe nel campo da gioco */
	@FXML
    private List<ImageView> imageTris;
	/*Lista di AnchorPane della parte destra della schermata*/
	@FXML
	private List<AnchorPane> anchorList;  
	/*Label del New game*/
	@FXML
	private List<Pane> backgroundLabel;   
	/*Lista di label in cui compaiono i nomi dei giocatori*/
	@FXML
	private List<Label> labelName;       
	/*Lista di label che compaiono nella pagine delle statistiche*/
	@FXML
	private List<Label> labelStats;		
	/*Cordinata X della schermata principale*/
    private double x;
    /*Cordinata Y della schermata principale*/
    private double y;						
    /*Lista dei nomi degli AnchorPane utile per settarli attraverso un unico ciclo*/
    private ArrayList<String> nameAnchor;	
    /*Oggetto in cui si calcolano i vari algoritmi di gioco*/
    private Algorithm game;
    /*Oggetto in cui si calcolano le varie statistiche di gioco*/				
    private Stats statistics;		
    /*Oggetto che mette in comunicazione i vari giocatori in Lan*/	
    private Server server;
	
    @Override
    /**
    * Funzione che viene richiamata all'apertura del file FXML e inizializzo la schermata con i vari settaggi
    * @param url url del controller 
    * @param rb bundle di risorse...
    */
	public void initialize(URL url, ResourceBundle rb) 
    {  	    	
    	statistics = new Stats();
    	nameAnchor = new ArrayList<String>();
    	
    	x = 0;
    	y = 0;
    	
    	makeDragable();
    	setNameAnchor();
    }

    /**
    * Funziona grapica per lo spostamento della schermata che imposta un principio di trasparenza carino da vedere
    */
	private void makeDragable() 
    {
		parentGame.setOnMousePressed(((event) -> {
            x = event.getSceneX();
            y = event.getSceneY();
        }));

		parentGame.setOnMouseDragged(((event) -> {
            Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
            stage.setX(event.getScreenX() - x);
            stage.setY(event.getScreenY() - y);
            stage.setOpacity(0.8f);
        }));

		parentGame.setOnDragDone(((event) -> {
            Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
            stage.setOpacity(1.0f);
        }));

		parentGame.setOnMouseReleased(((event) -> {
            Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
            stage.setOpacity(1.0f);
        }));
    }
	
	/**
    * Imposto ogni nome che identifica ogni elemento che corrisponde all'AnchorPane
    */
	private void setNameAnchor() 
    {
    	nameAnchor.add("anchorPlay");
    	nameAnchor.add("anchorStats");
    	nameAnchor.add("anchorChat");
	}

	/**
    * Funzione chiamata prima dell'apertura dll'applicazione in modo da settare tutte le variabile per poi renderle grafica
    * @param userOne nome del primo giocatore
    * @param userTwo nome del secondo giocatore
    * @param mode modalitadel gioco che ci interessa far partire
    * @param ip ip letto durante i vari controlli
    * @param nPort numero della porta che dobbimao aprire per mettere in comunicazione il server e il client
    */
	public void setVariables(String userOne, String userTwo, int mode, String ip, String nPort)
	{		
		game = new Algorithm(userOne, userTwo,  mode);
		if(mode == 2)
		{
			game.setNamePlayerTwo(ip);
			server  = new Server(ip, Integer.parseInt(nPort), this); 
		}
		
		setScreen();
	}
	
	/**
    * Setta lo schermata principale 
    */	
	private void setScreen() 
	{
		imageSettings.get(0).setImage(new Image("Pad.png"));
		imageSettings.get(1).setImage(new Image("Stats.png"));
		imageSettings.get(2).setImage(new Image("Chat.png"));
		imageSettings.get(3).setImage(new Image("Exit.png"));
		imageSettings.get(4).setImage(new Image("Send.png"));
		
		buttonSettings.get(0).setDisable(true);
		
		if(game.getMode() != 2)
			buttonSettings.get(2).setDisable(true);
		
		for(int i = 0; i < labelName.size(); i++)
		{
			labelName.get(i).setText(game.getNamePlayerOne());
			if(i%2 == 1)
				labelName.get(i).setText(game.getNamePlayerTwo());	
		}		
		textArea.setEditable(false);
		
		resetGameField();
	}

	/**
    * Visualizzazione della schermata in base alla categoria selezionata
    * @param event azione che viene compiione dalla pressione del bottone
    */
	public void setAnchor(ActionEvent event)
    {    	    	    	
    	String nameEvent = "anchor" + ((Node) event.getSource()).getId();
    	
    	int indexEvent = nameAnchor.indexOf(nameEvent);
    	
    	translationAnchor(indexEvent);
    }
	
	/**
    * Transizione di ogni anchorPane in base al bottone in cui ci andiamo a porre
    * @param index indice dell'array in cui compare quell'AnchorPane
    */
	private void translationAnchor(int index)
    {
    	hideAnchor();
    	
    	anchorList.get(index).setVisible(true);
    	buttonSettings.get(index).setDisable(true);	
    }
	
	/**
    * Nascondo tutti gli anchor e riattivo tutti i bottoni
    */
	private void hideAnchor()
    {
    	for(AnchorPane anchor : anchorList)
    		anchor.setVisible(false);
    	
    	for(Button button : buttonSettings)
    		button.setDisable(false);
    	
    	if(game.getMode() != 2)
			buttonSettings.get(2).setDisable(true);
    }
	
	/**
	*Funzione del gioco in base al bottone premuto nel campo di gioco eseguo un algoritmo
	* @param event evento del bottone premuto
	*/
	public void btnPremuto(ActionEvent event)
	{
		String btnPressed[] = ((Node) event.getSource()).getId().split("btn");
		int numPressed      = Integer.parseInt(btnPressed[1]);
				
		if(game.getMode() == 2)
			lanAlgorithm(numPressed);
		else
			startProcessGame(numPressed);
	}
	
	/**
	* Avvio del processo di gioco
	* @param numPressed numero premuto che si calcola in base all'evento del bottone
	*/
	private void startProcessGame(int numPressed)
	{
		if(game.isMovePossible(numPressed) && game.canContinue())
		{					
			setControlImage(numPressed);
			
			startAlgorithm(numPressed);
			
			setControlGraphic();
		}
	}
	
	/**
	* Avvio dell'algoritmo corretto in base alla modalita' scelta in precedenza dal menu
	* @param numPressed numero premuto del bpttpne sul campo di gioco
	*/
	private void startAlgorithm(int numPressed)
	{
		if(game.getMode() == 0)
			game.algorithmPlayer(numPressed);
		
		else if(game.getMode() == 1)
		{
			game.algorithmPlayer(numPressed);
			cpuMode(numPressed);
		}
	}
	
	/**
	* Algoritmo da avviare nel caso in cui e' stata richiesta la modalita' Lan 
	* @param numPressed numero premuto del bpttpne sul campo di gioco
	*/
	private void lanAlgorithm(int numPressed)
	{
		if(server.getAccepted() && game.isMovePossible(numPressed))
		{
			if(server.getYourTurn() && !server.getUnableConn() && game.canContinue()) 
			{
				setControlImage(numPressed);
				game.algorithmPlayer(numPressed);
				server.setYourTurn(false);
				server.sendNumPressed(numPressed);
				setControlGraphic();
			}
		}
	}
	
	/**
	* Mossa che deve essere eseguita dal ricevitore del Lan
	* @param numPressed numero premuto del bpttpne sul campo di gioco
	*/
	public void lanMoves(int numPressed)
	{
		if(game.isMovePossible(numPressed) && game.canContinue())
		{
			setControlImage(numPressed);
			game.algorithmPlayer(numPressed);
			setControlGraphic();
		}
	}
	
	/**
	* Mossa che deve compiore la cpu dopo la mossa del giocatore
	* @param numPressed numero premuto del bpttpne sul campo di gioco
	*/
	private void cpuMode(int numPressed)
	{
		if(game.canContinue())
		{
			int numPressedCpu = game.IA(numPressed);
			if(numPressedCpu != -1)
			{
				setControlImage(numPressedCpu);
				game.algorithmPlayer(numPressedCpu);
				setControlGraphic();
			}
		}
	}
	
	/**
	* Controlli grafici da eseguire dopo ogni operazione
	*/
	private void setControlGraphic()
	{
		if(game.canContinue())	
			setBackgroundLabel();
		else if(!game.isTie())
			setGraphicWIN();
	}

	/**
	* Immagine da mettere nel campo da gioco in base alla posizione
	* @param numPressed numero premuto del bpttpne sul campo di gioco
	*/
	private void setControlImage(int numPressed)
	{
		if(game.getTurn()%2 == 0)
			imageTris.get(numPressed).setImage(new Image("X.png"));
		else
			imageTris.get(numPressed).setImage(new Image("O.png"));	
	}
	
	/**
	* Settaggio dello sfondo del giocatore che deve giocare
	*/
	private void setBackgroundLabel()
	{	
		if(game.getTurn()%2 == 0)
		{
			backgroundLabel.get(0).setStyle("-fx-background-color: " + Constants.LIGHT_GREEN);
			backgroundLabel.get(1).setStyle("-fx-background-color: " + Constants.TRANSPARENT);
		}
		else
		{
			backgroundLabel.get(1).setStyle("-fx-background-color: " + Constants.LIGHT_GREEN);
			backgroundLabel.get(0).setStyle("-fx-background-color: " + Constants.TRANSPARENT);
		}
	}
	
	/**
	* Azioni logiche e grafiche da compiore nel caso di vittoria
	*/
	private void setGraphicWIN()
	{	
		int position[] = game.positionsWin();
		for(int i = 0; i < position.length; i++)
			buttonPlay.get(position[i]).setStyle("-fx-background-color: " + Constants.LIGHT_GREEN);
	}
	
	/**
	* Azioni grafiche da far fare al client nella modalita' Lan
	*/
	public void graphicClient()
	{
		game.setTurnClient();
	}
	
	/**
	* reset grafico e logico nel caso del New Game
	*/
	public void newGame()
	{
		statistics.addGamePlayed();
		if(game.isWon())
			statistics.addWinPlayerOne();
		if(game.isEnemyWon())
			statistics.addWinPlayerTwo();
		setLabelStats();
		
		game.resetGame();
		resetGameField();
	}
	
	/**
	* Imposto le Label con i dati letti dalle statistiche
	*/
	private void setLabelStats() 
	{
		ArrayList<String> value = new ArrayList<String>();
		value.add(statistics.getGamePlayed());
		value.add(statistics.getWinPlayerOne());
		value.add(statistics.getWinPlayerTwo());
		value.add(statistics.getDraw());
		value.add(statistics.getPercent());
		
		for(int i = 0; i < labelStats.size(); i++)
			labelStats.get(i).setText(value.get(i));
	}
	
	/**
	* Resetto il terreno di gioco cancellando le immagini
	*/
	private void resetGameField() 
	{		
		for(ImageView image: imageTris)
			image.setImage(new Image("Null.png"));
		
		for(Button btn: buttonPlay)
			btn.setStyle("-fx-background-color: " + Constants.BACKGROUND);
		
		setBackgroundLabel();
	}
	
	/**
	* Invio del messaggio al Lan
	*/
	public void send()
	{
		String messageText = game.getNamePlayerOne() + " : " + message.getText();
		if(!messageText.equals(game.getNamePlayerOne() + " : "))
		{
			textArea.appendText(messageText + "\n");
			message.clear();
			server.sendMessage(messageText+ "\n");
		}
	}
	
	/**
	* Lettura del messaggio dal Lan
	* @param charMessage carattere letto durante la routine del thread dedicato alla lettura
	*/
	public void readMessage(char charMessage)
	{
		if(message != null)
			textArea.appendText(charMessage + "");
	} 
	
	/**
	*Exit dall'applicazione
	*/
	public void exit()
    {    	
		if(game.getMode() == 2)
			server.exit();
		//System.exit(0);
    	try 
    	{
    		FXMLLoader loader = new FXMLLoader(getClass().getResource("Menu.fxml"));
    		
    		Parent root = (Parent) loader.load();
    		MenuController menuController = loader.getController();
    		menuController.setUsernameTextField(labelName.get(0).getText());
    		
			Stage stage = new Stage();
			Scene scene = new Scene(root);
			    
			scene.setFill(Color.TRANSPARENT);		         
			stage.setScene(scene);		        
			stage.setTitle(Constants.TITLE_MENU);
			stage.initStyle(StageStyle.TRANSPARENT);
			stage.show();
    	} 
    	catch(Exception e) 
    	{
    		 e.printStackTrace();
    	}
    	Stage toClose = (Stage)parentGame.getScene().getWindow();
    	toClose.close();
    }
    
  
}

