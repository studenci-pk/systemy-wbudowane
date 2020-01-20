import javafx.application.Application;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.TextArea;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

import java.io.*;

public class Main extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        FXMLLoader loader = new FXMLLoader(getClass().getResource("/main.fxml"));
        Pane centralPane = loader.load();
        Scene scene = new Scene(centralPane);
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    @FXML
    public TextArea textArea;

    @FXML
    public void initialize() {
        Thread thread = new Thread(() -> {
            File file = new File("/home/przemek/CLionProjects/sw_projekt/output.txt");
            try {

                while (true) {
                    Thread.sleep(10);

                    BufferedReader buffer = new BufferedReader(new FileReader(file));
                    StringBuilder sb = new StringBuilder();
                    String line = buffer.readLine();

                    while (line != null) {
                        sb.append(line);
                        sb.append(System.lineSeparator());
                        line = buffer.readLine();
                    }
                    textArea.setText(sb.toString());

                    buffer.close();
                }

            } catch (InterruptedException | IOException e) {
                e.printStackTrace();
            }
        });

        thread.setDaemon(true);
        thread.start();
    }
}
