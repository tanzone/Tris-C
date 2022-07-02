/**
 * @(#)MenuController.java
 *
 * Controller del file Menu.fxml che gestisce tutti i componenenti e implementa le funzioni principali che appaiono nel menu
 * @author Tanzi Manuel
 * @version 1.00 13/09/2018
 */

import java.net.InetAddress;
import java.net.URL;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;
import java.util.regex.Matcher;

import javafx.animation.FadeTransition;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import javafx.util.Duration;


public class MenuController implements Initializable
{   
    /*AnchorPane principale che racchiude tutto al suo interno*/
    @FXML
    private AnchorPane parent;
    /*Lista di componenti che appartengono al menuBar */
    @FXML
    private List<MenuItem> menuList;
    /*Lista dei bottoni che compaiono nel menu*/
    @FXML
    private List<Button> buttonList;
    /*Lista di AnchorPane della parte destra della schermata*/
    @FXML
    private List<AnchorPane> anchorList;
    /*Lista di TextField che compaiono nei vari AnchorPane selezionabili*/
    @FXML
    private List<TextField> textFieldList;
    /*Immagine di background che identifica ogni categoria*/
    @FXML
    private ImageView image;
    /*Immagine del bottoncino del quit*/
    @FXML
    private ImageView imageQuit;
    /*Label in cui viene scritto il prorpio Ip della macchina*/
    @FXML
    private Label labelIp;
    /*Label in cui compare il proprio nome dopo averlo settato*/
    @FXML
    private Label user;
    /*Label che identifica se c'e' stato un errore nell'inserimento di qualche dato*/
    @FXML
    private Label error;
    /*Cordinata X della schermata principale*/
    private double x;
    /*Cordinata Y della schermata principale*/
    private double y;
    /*Stringa in cui viene riportato il nome dell'immagine che bisogna inserire nel background*/
    private String imageValue;
    /*Lista dei nomi degli AnchorPane utile per settarli attraverso un unico ciclo*/
    private ArrayList<String> nameAnchor;

    @Override
    /**
    * Funzione che viene richiamata all'apertura del file FXML e inizializzo la schermata con i vari settaggi
    * @param url url del controller 
    * @param rb bundle di risorse...
    */
    public void initialize(URL url, ResourceBundle rb) 
    {  	
    	nameAnchor = new ArrayList<String>();
    	
    	x = 0;
    	y = 0;
    	imageValue = "PlayerVsPlayer";
    	
    	makeDragable();
    	setNameAnchor();
    	setActionMenuList(menuList.size());
        setScreen();
        setIp();
    }
	
    /**
    * Funziona grapica per lo spostamento della schermata che imposta un principio di trasparenza carino da vedere
    */
	private void makeDragable() 
    {
        parent.setOnMousePressed(((event) -> {
            x = event.getSceneX();
            y = event.getSceneY();
        }));

        parent.setOnMouseDragged(((event) -> {
            Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
            stage.setX(event.getScreenX() - x);
            stage.setY(event.getScreenY() - y);
            stage.setOpacity(0.8f);
        }));

        parent.setOnDragDone(((event) -> {
            Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
            stage.setOpacity(1.0f);
        }));

        parent.setOnMouseReleased(((event) -> {
            Stage stage = (Stage) ((Node) event.getSource()).getScene().getWindow();
            stage.setOpacity(1.0f);
        }));
    }
	
    /**
    * Imposto ogni nome che identifica ogni elemento che corrisponde all'AnchorPane
    */
	private void setNameAnchor() 
    {
    	nameAnchor.add("anchorImages");
    	nameAnchor.add("anchorPlayerVsPlayer");
    	nameAnchor.add("anchorPlayerVsCpu");
    	nameAnchor.add("anchorLan");
    	nameAnchor.add("anchorSettings");
	}

    /**
    * Imposto un azione da far fare agli elementi che ci sono nel menu bar in modo ricorsivo
    * @param num corrisponde all'indice della lista di array degli AnchorPane
    */
	private void setActionMenuList(int num) 
    {
		if(num == 0) return;
		
		menuList.get(num-1).setOnAction((event) -> { translationAnchor(num); });
		
		setActionMenuList(num-1);
	}
	
    /**
    * Setta lo schermata principale 
    */
    private void setScreen() 
    {   	
    	setBackground(null);

    	imageQuit.setImage(new Image("Quit.png")); 	
    }
    
    /**
    * Ricavo l'IP della macchina e lo stampo nell'apposita Label
    */
    private void setIp() 
    {
    	try 
    	{
			labelIp.setText("" + (InetAddress.getLocalHost().getHostAddress()).trim());
		} 
    	catch(UnknownHostException e) 
    	{
    		labelIp.setText(" Can't catch your IP");
		}
	}
    
    /**
    * Transizione di ogni anchorPane in base al bottone in cui ci andiamo a porre
    * @param index indice dell'array in cui compare quell'AnchorPane
    */
    private void translationAnchor(int index)
    {
    	hideAnchor();
    	
    	anchorList.get(index).setVisible(true);
		buttonList.get(index-1).setDisable(true);	
    }

    
    /**
    * Settaggio dello sfondo in base a dove si trova il mouse
    * @param event evento del muose che compie 
    */
    public void setBackground(MouseEvent event)
    {
    	hideAnchor();
    	anchorList.get(0).setVisible(true);
    	
    	if(event == null)
    	{
    		image.setImage(new Image(imageValue + ".jpg"));
    		fadeIn();
    	}
    	else
    	{
    		String nameEvent = ((Node) event.getSource()).getId();
    	
    		if(!imageValue.equals(nameEvent))
    		{
    			image.setImage(new Image(((Node) event.getSource()).getId() + ".jpg"));
    			fadeIn();
    		}
    		imageValue = nameEvent;
    	}
    }
    
    /**
    * Effetto speciale di dissolvenza per l'immagine
    */
    private void fadeIn()
    {
    	FadeTransition fadeIn = new FadeTransition(Duration.seconds(2), image);
    	fadeIn.setFromValue(0.0);
    	fadeIn.setToValue(1.0);
    	fadeIn.play();
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
    * Nascondo tutti gli anchor e riattivo tutti i bottoni
    */
    private void hideAnchor()
    {
    	for(AnchorPane anchor : anchorList)
    		anchor.setVisible(false);
    	
    	for(Button button : buttonList)
    		button.setDisable(false);	
    }
    
    /**
    * Alla conferma dei dati inseriti nel setting imposto il nome come User 
    */
    public void confirm()
    {	
    	String userName = textFieldList.get(0).getText();
    	
    	if(userName.equals(""))
    		userName = textFieldList.get(0).getPromptText();
    		
    	setUsernameTextField(userName);
    }
    
    /**
    * Imposto questo nome in ogni prompt dei textfield che corrispondono al primo giocatore
    * @param userName username che viene letto dal textfield del setting
    */
    public void setUsernameTextField(String userName)
    {
    	int[] settingText = {0,1,3,4};
    	
    	user.setText(userName);
    	
    	for(int i = 0; i < settingText.length; i++)
    	{
    		textFieldList.get(settingText[i]).setPromptText(userName);
    		textFieldList.get(settingText[i]).clear();
    	}
    }
       
    /**
    * Avvio la modalita 1 v 1
    */
    public void startVersus()
    {
    	String userTwo = textFieldList.get(5).getText();
    	    	
    	if(userTwo.equals(""))
    		userTwo = "Unknown";
    	
    	 textFieldList.get(5).clear();
    	 
    	 startNewFXML(namePlayerOne(4), userTwo, 0, null, null);
    }
    
    /**
    * Avvio la modalita 1 v CPU
    */
    public void startCpu()
    {    	
    	startNewFXML(namePlayerOne(3), Constants.NAME_CPU , 1, null, null);
    }
    
    /**
    * Avvio la modalita LAN prendendo i vari dati inseriti e controllandoli se sono corretti
    */
    public void startLan()
    {    	
    	String ip    = textFieldList.get(2).getText();
    	String nPort = textFieldList.get(6).getText();
    	
    	if(ip.equals("") || ip.equals(Constants.LOCALHOST))
    		ip = labelIp.getText();
    	if(nPort.equals(""))
    		nPort = textFieldList.get(6).getPromptText();
    	
    	if(validateIp(ip) && validatePort(nPort))
    	{
    		error.setText("");
    		startNewFXML(namePlayerOne(1), null, 2, ip, nPort);
    	}
    	else
    		error.setText(Constants.ERROR_LAN);
    }
    
    /**
    * Cattura del nome del primo player
    * @param textField indice dell'array del textField interessato e leggerne le proprieta'
    * @return il nome del primo giocatore
    */
    private String namePlayerOne(int textField)
    {
    	String userOne = textFieldList.get(textField).getText();
    	
    	if(userOne.equals(""))
    		userOne = user.getText();
    	
    	textFieldList.get(textField).clear();
    	
    	return userOne;
    }
    
    /**
    * Controllo la validita' dell'indirizzo IP inserito
    * @param ip ip inserito 
    * @return true se e' corretto, false altrimenti
    */
    private boolean validateIp(String ip)
    {
    	Matcher matcher = Constants.IPV4_PATTERN.matcher(ip);

		return matcher.matches();
    }
    
    /**
    * Controllo la validita' ella porta inserita
    * @param port numero porta inserita 
    * @return true se e' corretto, false altrimenti
    */
    private boolean validatePort(String port)
    {
    	return (Integer.parseInt(port) > Constants.N_MIN_PORT || Integer.parseInt(port) < Constants.N_MAX_PORT);

    }
    
    /**
    * Avvio del nuovo FXML e chiusura di quello attuale
    * @param userOne nome del primo giocatore
    * @param userTwo nome del secondo giocatore
    * @param mode modalitadel gioco che ci interessa far partire
    * @param ipLoad ip letto durante i vari controlli
    * @param nPortLoad numero della porta che dobbimao aprire per mettere in comunicazione il server e il client
    */
    private void startNewFXML(String userOne, String userTwo, int mode, String ipLoad, String nPortLoad)
    {
    	try 
    	{
    		FXMLLoader loader = new FXMLLoader(getClass().getResource("Play.fxml"));
    		
    		Parent root = (Parent) loader.load();
    		GameController gameController = loader.getController();
    		gameController.setVariables(userOne, userTwo, mode, ipLoad, nPortLoad);
    		
			Stage stage = new Stage();
			Scene scene = new Scene(root);
			    
			scene.setFill(Color.TRANSPARENT);		         
			stage.setScene(scene);		        
			stage.setTitle(Constants.TITLE_PLAY);
			stage.initStyle(StageStyle.TRANSPARENT);
			stage.show();
    	} 
    	catch(Exception e) 
    	{
    		 e.printStackTrace();
    	}
    	Stage toClose = (Stage)parent.getScene().getWindow();
    	toClose.close();
    }
    
    /**
     * Metto a video tutte le informazioni inerenti il mio programma utilizzando un JPanel Message
     */
    public void aboutApp()
    {
    	Alert alert = new Alert(AlertType.INFORMATION);
    	alert.setTitle("About my application");
    	alert.setHeaderText("This game was created by Manuel Tanzi.");
    	alert.setContentText("THE GAME INCLUDE:\n- Player vs Player in which two players compete on the same window and once per turn will make their move.\n- "
    			+ "Player vs CPU where the difficulty level is set automatically on impossible so that it is only possible to lose or at best draw. Do not believe, TRY IT!\n- "
    			+ "Lan allows you to connect in lan with an opponent.\n -"
    			+ "Settings you can change your username and verify your IP\n\n"
    			+ "Once you have entered the game screen you will be given the opportunity to go and check your game statistics and if you are playing in lan mode you can chat with your opponent.");

    	alert.showAndWait();
    }
    
    /**
    *Uscita e chiusura di tutto
    */
    public void exit()
    {
    	System.exit(0);
    }
}