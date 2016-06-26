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
import javax.swing.filechooser.*;
/*
 * SwingFileChooserDemo.java is a 1.4 application that uses these files:
 * images/Open16.gif images/Save16.gif
 */
public class SwingFileChooserDemo extends JPanel implements ActionListener {
  static private final String newline = "\n";

  JButton openButton; //, saveButton;

  JTextArea log;

  JFileChooser fc;

  public SwingFileChooserDemo() {
    super(new BorderLayout());

    //Create the log first, because the action listeners
    //need to refer to it.
    log = new JTextArea(10, 40);
    log.setMargin(new Insets(5, 5, 5, 5));
    log.setEditable(false);
    //JScrollPane logScrollPane = new JScrollPane(log);

    //Create a file chooser
    fc = new JFileChooser();
     FileFilter imageFilter = new FileNameExtensionFilter("Image files", ImageIO.getReaderFileSuffixes());
    fc.addChoosableFileFilter(imageFilter);
    fc.setAcceptAllFileFilterUsed(false);

    //Uncomment one of the following lines to try a different
    //file selection mode. The first allows just directories
    //to be selected (and, at least in the Java look and feel,
    //shown). The second allows both files and directories
    //to be selected. If you leave these lines commented out,
    //then the default mode (FILES_ONLY) will be used.
    //
    //fc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
    //fc.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);

    //Create the open button. We use the image from the JLF
    //Graphics Repository (but we extracted it from the jar).
    openButton = new JButton("Open a File...");
        //createImageIcon("images/Open16.gif"));
    openButton.addActionListener(this);

    //For layout purposes, put the buttons in a separate panel
    JPanel buttonPanel = new JPanel(); //use FlowLayout
    buttonPanel.add(openButton);
    //buttonPanel.add(saveButton);

    //Add the buttons and the log to this panel.
    add(buttonPanel, BorderLayout.PAGE_START);
    add(log, BorderLayout.CENTER);
    //add(logScrollPane, BorderLayout.CENTER);
    //add(imageFrame, BorderLayout.CENTER);
  }


  public void actionPerformed(ActionEvent e) {

    //Handle open button action.
    if (e.getSource() == openButton) {
        fc.setCurrentDirectory(new java.io.File("."));
        fc.setDialogTitle("choosertitle");

        if (fc.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {
          //System.out.println("getCurrentDirectory(): " + fc.getCurrentDirectory());
          String image_url = fc.getCurrentDirectory() + fc.getSelectedFile().getName();
          System.out.println(image_url);
          System.out.println("getSelectedFile() : " + fc.getSelectedFile());
          log.setText("Open image: " + image_url);

          // //problem!!!!
          // try{ 
          //   Process process = new ProcessBuilder("print").start();
          //   //"print" is an executable C++ program. You can change its name.
          //   //We need to pass image_url as argv to this executable program
          //   BufferedReader output = getOutput(process);
          //   String ligne = "";
          //   while ((ligne = output.readLine()) != null) {
          //      System.out.println(ligne);
          //   }
          // }
          // catch(IOException err){
          // }
    

        } else {
          System.out.println("No Selection ");
        }

      } else {
        log.append("Open command cancelled by user." + newline);
      }
      log.setCaretPosition(log.getDocument().getLength());
  } 

  /**
   * Create the GUI and show it. For thread safety, this method should be
   * invoked from the event-dispatching thread.
   */
  private static void createAndShowGUI() {
    //Make sure we have nice window decorations.
    JFrame.setDefaultLookAndFeelDecorated(true);
    JDialog.setDefaultLookAndFeelDecorated(true);

    //Create and set up the window.
    JFrame frame = new JFrame("SwingFileChooserDemo");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    //Create and set up the content pane.
    JComponent newContentPane = new SwingFileChooserDemo();
    newContentPane.setOpaque(true); //content panes must be opaque
    frame.setContentPane(newContentPane);

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