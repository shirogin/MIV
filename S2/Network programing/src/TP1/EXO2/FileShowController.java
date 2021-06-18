package TP1.EXO2;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.*;

public class FileShowController {
    @FXML
    private TextArea text;
    @FXML
    private Button openButton, closeButton;


    @FXML
    private void open() {
        FileChooser fc = new FileChooser();
        fc.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("Text Files", "*.txt")
        );

        File selectedFile = fc.showOpenDialog(null);
        if (selectedFile != null) {
            InputStream is;
            try {
                is = new FileInputStream(selectedFile.getAbsoluteFile());
                byte[] b = new byte[50];
                StringBuilder s= new StringBuilder();
                while (is.read(b) != -1) {
                    s.append(new String(b));
                }
                this.text.setText(s.toString());
                is.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    @FXML
    private void exit() {
        Stage stage = (Stage) closeButton.getScene().getWindow();
        stage.close();
    }
}
