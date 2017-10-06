import java.applet.Applet;
import java.awt.*;
import java.awt.event.*;
import java.util.Properties;

public class ComponentApplet extends Applet {
	Button printButton = new Button("print ...");

	static Frame getFrame(Component c) {
		while((c = c.getParent()) != null) {
			if(c instanceof Frame)
				return (Frame)c;
		}
		return null;
	}
	static void printComponents(Component c) {
		Toolkit    tk    = Toolkit.getDefaultToolkit();
		Frame      frame = getFrame(c);
		Properties props = new Properties();

		props.put("awt.print.printer",   "durango");
		props.put("awt.print.numCopies", "2");

		if(tk != null) {
			String   name = c.getName() + " print job";
			PrintJob pj   = tk.getPrintJob(frame, name, props);

			if(pj != null) {
				Graphics pg = pj.getGraphics();

				if(pg != null) {
					c.printAll(pg);
					pg.dispose();
				}
				pj.end();
			}
			System.out.println(props);
		}
	}
	public void init() {
		ScrollbarPanel sbarPanel;
		Panel     checkboxPanel;
		Label     label     = new Label("A Label");
		Canvas    canvas    = new TestCanvas();
		Button    button    = new Button("A Button");
		TextField tf        = new TextField("A Textfield");
		TextArea  ta	    = new TextArea("TextArea", 5, 20);
		List      list      = new List(10, true);
		Choice    choice    = new Choice();

		printButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				printComponents(ComponentApplet.this);
			}
		});

		checkboxPanel = new CheckboxPanel();
		sbarPanel     = new ScrollbarPanel();

		list.add("One");
		list.add("Two");
		list.add("Three");
		list.add("Four");
		list.add("Five");
		list.add("Six");
		list.add("Seven");
		list.add("Eight");
		list.add("Nine");
		list.add("Ten");
		list.add("Eleven");
		list.add("Twelve");
		list.add("Thirteen");
		list.add("Fourteen");
		list.add("Fiveteen");
		list.add("Sixteen");
		list.add("Seventeen");
		list.add("Eightteen");
		list.add("Nineteen");
		list.add("Twenty");

		choice.add("Buffalo Sabres");
		choice.add("Boston Bruins");
		choice.add("Colorado Avalanche");
		choice.add("Florida Panthers");
		choice.add("New Jersey Devils");
		choice.add("Philadelphia Flyers");
		choice.add("San Jose Sharks");

		Panel scrollMe = new ScrollMe();
		scrollMe.setLayout(
			new FlowLayout(FlowLayout.CENTER, 10, 10));

		scrollMe.add(printButton);
		scrollMe.add(canvas);
		scrollMe.add(button);
		scrollMe.add(tf);
		scrollMe.add(ta);
		scrollMe.add(list);
		scrollMe.add(choice);
		scrollMe.add(checkboxPanel);
		scrollMe.add(label);
		scrollMe.add(sbarPanel);

		ScrollPane scroller = new ScrollPane();
		scroller.add(scrollMe);
		setLayout(new BorderLayout());
		add("Center", scroller);
	}
}

class ScrollMe extends Panel {
	public Dimension getPreferredSize() {
		return new Dimension(250,500);
	}
}
class CheckboxPanel extends Panel {
	public CheckboxPanel() {
		Panel checkboxPanel = new Panel();
		CheckboxGroup group = new CheckboxGroup();

		checkboxPanel.setLayout(new GridLayout(3,0));
		checkboxPanel.add(
			new Checkbox("bordered",    group, false));
		checkboxPanel.add(
			new Checkbox("transparent", group, false));
		checkboxPanel.add(
			new Checkbox("continuous",  group, true));

		setLayout(new BorderLayout(10,10));
		add("Center", checkboxPanel);
	}
	public void paint(Graphics g) {
		g.drawRect(0,0,getSize().width-1,getSize().height-1);
	}
}

class TestCanvas extends Canvas {
	public void paint(Graphics g) {
		FontMetrics fm   = g.getFontMetrics();
		Dimension   size = getSize();
		String      str  = "A Canvas";

		g.drawRect(0,0,size.width-1,size.height-1);
		g.drawString(str, 
				     (size.width/2) - (fm.stringWidth(str)/2),
		             (size.height/2) - (fm.getHeight()/2) + 
					  fm.getAscent());
	}
	public Dimension getPreferredSize() {
		return new Dimension(100,100);
	}
}

class ScrollbarPanel extends Panel {
	public ScrollbarPanel() {
		Scrollbar sbar = new Scrollbar(Scrollbar.HORIZONTAL);
		setLayout(new BorderLayout(10,10));
		add("Center", sbar);
	}
	public Dimension getPreferredSize() {
		return new Dimension(200,20);
	}
}
