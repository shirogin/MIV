package TP2;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Stage;
import javafx.stage.StageStyle;

import java.io.IOException;

public class FileShow extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        try {
            Parent root = FXMLLoader.load(getClass().getResource("FileShow.fxml"));
            Scene scene = new Scene(root);
            primaryStage.setScene(scene);
            primaryStage.initStyle(StageStyle.TRANSPARENT);
            primaryStage.setTitle("Show file");
            /*
            * scene.setFill(Color.TRANSPARENT);
            * scene.getStylesheets().add(getClass().getResource("/sample/style.css").toExternalForm());
            * primaryStage.getIcons().add(new Image("/logo.png"));
            */
            primaryStage.show();

        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
