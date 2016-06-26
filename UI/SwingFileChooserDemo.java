/* From http://java.sun.com/docs/books/tutorial/index.html */

/*
 * Copyright (c) 2006 Sun Microsystems, Inc. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * -Redistribution of source code must retain the above copyright notice, this
 *  list of conditions and the following disclaimer.
 *
 * -Redistribution in binary form must reproduce the above copyright notice,
 *  this list of conditions and the following disclaimer in the documentation
 *  and/or other materials provided with the distribution.
 *
 * Neither the name of Sun Microsystems, Inc. or the names of contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * This software is provided "AS IS," without a warranty of any kind. ALL
 * EXPRESS OR IMPLIED CONDITIONS, REPRESENTATIONS AND WARRANTIES, INCLUDING
 * ANY IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * OR NON-INFRINGEMENT, ARE HEREBY EXCLUDED. SUN MIDROSYSTEMS, INC. ("SUN")
 * AND ITS LICENSORS SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY LICENSEE
 * AS A RESULT OF USING, MODIFYING OR DISTRIBUTING THIS SOFTWARE OR ITS
 * DERIVATIVES. IN NO EVENT WILL SUN OR ITS LICENSORS BE LIABLE FOR ANY LOST
 * REVENUE, PROFIT OR DATA, OR FOR DIRECT, INDIRECT, SPECIAL, CONSEQUENTIAL,
 * INCIDENTAL OR PUNITIVE DAMAGES, HOWEVER CAUSED AND REGARDLESS OF THE THEORY
 * OF LIABILITY, ARISING OUT OF THE USE OF OR INABILITY TO USE THIS SOFTWARE,
 * EVEN IF SUN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 *
 * You acknowledge that this software is not designed, licensed or intended
 * for use in the design, construction, operation or maintenance of any
 * nuclear facility.
 */

import java.awt.BorderLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.ImageFilter;
import java.awt.Image;
import java.io.File;
import java.io.IOException;
import java.io.OutputStream;
import java.io.BufferedReader;
import java.io.InputStream;
import java.awt.Color;

import javax.imageio.ImageIO;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.border.*;
import javax.swing.filechooser.*;
import javax.swing.BorderFactory;
import javax.swing.JOptionPane;

/*
 * SwingFileChooserDemo.java is a 1.4 application that uses these files:
 * images/Open16.gif images/Save16.gif
 */
public class SwingFileChooserDemo extends JPanel implements ActionListener {
  static private final String newline = "\n";
  JButton openTemplateButton; //, saveButton;
  JButton openTestButton;
  JButton runButton;

  //record the path!!!
  static String templatePath = "";
  static String testPath = "";

  JTextArea log;

  JFileChooser fc;
  //JFileChooser fcTest;

  public SwingFileChooserDemo(String image_name) {
    super(new BorderLayout());

    if (image_name.equals("run")){
        JPanel buttonPanel = new JPanel(); //use FlowLayout
        runButton = new JButton("run");
        runButton.addActionListener(this);
        buttonPanel.add(runButton, BorderLayout.CENTER);
        add(buttonPanel);
        return;
    } 

    //Create the log first, because the action listeners
    //need to refer to it.
    log = new JTextArea(10, 40);
    log.setMargin(new Insets(5, 5, 5, 5));
    log.setEditable(false);

    //Create a file chooser
    fc = new JFileChooser();
     FileFilter imageFilter = new FileNameExtensionFilter("Image files", ImageIO.getReaderFileSuffixes());
    fc.addChoosableFileFilter(imageFilter);
    fc.setAcceptAllFileFilterUsed(false);


    //Create the open button. We use the image from the JLF
    //Graphics Repository (but we extracted it from the jar).
    JPanel buttonPanel = new JPanel();
    if (image_name.equals("template")){
       openTemplateButton = new JButton("Open a " + image_name + " image" );
       openTemplateButton.addActionListener(this);
       buttonPanel.add(openTemplateButton);
     }else if (image_name.equals("test")){
       openTestButton = new JButton("Open a " + image_name + " image" );
       openTestButton.addActionListener(this);
       buttonPanel.add(openTestButton);
     }

    //Add the buttons and the log to this panel.
    add(buttonPanel, BorderLayout.PAGE_START);
    add(log, BorderLayout.CENTER);
  }



public void actionPerformed(ActionEvent e) {
//Handle open button action.
if (e.getSource() == openTemplateButton || e.getSource() == openTestButton) {
    fc.setCurrentDirectory(new java.io.File("."));
    fc.setDialogTitle("choosertitle");

    if (fc.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
      String path = fc.getCurrentDirectory() + fc.getSelectedFile().getName();
      System.out.println(path);
      System.out.println("getSelectedFile() : " + fc.getSelectedFile());
      log.setText("Open image: " + path);

      if (e.getSource() == openTemplateButton)
          templatePath = new String(path);
      else
          testPath = new String(path);
    }
     else {
      System.out.println("No Selection ");
    }

  } else if (e.getSource() == runButton){
    //to be implemented
    if (templatePath.equals("") || testPath.equals("")){
      JOptionPane.showMessageDialog(null, "No image", "Error",
                                    JOptionPane.ERROR_MESSAGE);
    }

      // //problem!!!!
      // try{ 
      //   System.out.println("Start");
      //   //Process process = new ProcessBuilder("../tempExe").start();
      //   Process process = Runtime.getRuntime().exec("../tempExe");
      //   //int exitCode = process.waitFor();
      //   System.out.println("End");
      // }
      // catch(IOException err){
      // }

    String filePath = "../tempExe";
      if (new File(filePath).exists()) {
          try {

              ProcessBuilder pb = new ProcessBuilder(filePath);
              pb.redirectError();
              Process p = pb.start();
              InputStream is = p.getInputStream();
              int value = -1;
              while ((value = is.read()) != -1) {
                  System.out.print((char) value);
              }

              int exitCode = p.waitFor();

              System.out.println(filePath + " exited with " + exitCode);
          } catch (Exception er) {
              er.printStackTrace();
          }
      } else {
          System.err.println(filePath + " does not exist");
      }
  }

  else {
    log.append("Open command cancelled by user." + newline);
  }
  //log.setCaretPosition(log.getDocument().getLength());
} 

  /**
   * Create the GUI and show it. For thread safety, this method should be
   * invoked from the event-dispatching thread.
   */
  private static void createAndShowGUI() {
    Border blackline = BorderFactory.createLineBorder(Color.black);
    //Make sure we have nice window decorations.
    JFrame.setDefaultLookAndFeelDecorated(true);
    JDialog.setDefaultLookAndFeelDecorated(true);

    //Create and set up the window.
    JFrame frame = new JFrame("SwingFileChooserDemo");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.getContentPane().setLayout(new BorderLayout());

    //Create and set up the content pane.
    JComponent newContentPaneTemplate = new SwingFileChooserDemo("template");
    newContentPaneTemplate.setBorder(blackline);
    newContentPaneTemplate.setOpaque(true); //content panes must be opaque
    frame.getContentPane().add(newContentPaneTemplate, BorderLayout.WEST);

        //Create and set up the content pane.
    JComponent newContentPaneTest = new SwingFileChooserDemo("test");
    newContentPaneTest.setBorder(blackline);
    newContentPaneTest.setOpaque(true); //content panes must be opaque
    frame.getContentPane().add(newContentPaneTest, BorderLayout.EAST);

    JPanel controlPanel = new SwingFileChooserDemo("run");
    frame.getContentPane().add(controlPanel, BorderLayout.SOUTH);

    //Display the window.
    frame.pack();
    frame.setVisible(true);
  }

  public static void main(String[] args) {
    //Schedule a job for the event-dispatching thread:
    //creating and showing this application's GUI.
    javax.swing.SwingUtilities.invokeLater(new Runnable() {
      public void run() {
        createAndShowGUI();
      }
    });
  }
}