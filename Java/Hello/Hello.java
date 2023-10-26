import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;

class MyJButton extends JButton {
  public MyJButton() {
    super("Edit");
    setSize(30, 16);
    addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent evt) {
        System.out.println("Button pressed.");
      }
    });
  }
}

class MyJFrame extends JFrame {
  public MyJFrame() {
    super("HelloWorld");

    setSize(600, 400);
    setLocation(300, 200);
    setDefaultCloseOperation(EXIT_ON_CLOSE);
    setVisible(true);

    btn = new MyJButton();
    btn2 = new MyJButton();
    add(btn);
    add(btn2);
  }

  private MyJButton btn, btn2;
}

public class Hello{
  public static void main(String[] args) {
    MyJFrame f = new MyJFrame();
  }
}