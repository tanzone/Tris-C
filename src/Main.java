/**
 * @(#)Main.java
 *
 * Main che apre l'FXML del menu creando un nuovo Stage in un nuovo thread
 * @author Tanzi Manuel
 * @version 1.00 13/09/2018
 */

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

public class Main extends Application 
{
	@Override
    public void start(Stage stage) throws Exception
    {
		Parent root = FXMLLoader.load(getClass().getResource("Menu.fxml"));
        
        Scene scene = new Scene(root);
        
        scene.setFill(Color.TRANSPARENT);
        
        stage.setScene(scene);
        
        stage.setTitle(Constants.TITLE_MENU);
        
        stage.initStyle(StageStyle.TRANSPARENT);
        
        stage.show();
    }

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)
    {
        launch(args);
    }  
}