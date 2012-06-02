import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.util.Vector;

import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;


public class Tu extends JFrame{
	Container c;
	JMenuBar jmb;
	JMenu jm;
	JMenuItem sl;
	JPanel p1,p1t1,p3,p3s,p3st1,p3t1,p3t2,p4,p5,pg;
	Box p2,p4t1,p5t1;
	JLabel pid;
	JLabel pidr;
	JLabel sup;
	JLabel supr;
	JLabel rtime;
	JLabel rtimer;
	JLabel ares;
	JLabel hresr;
	

	JTextField tpid;
	JTextField tpidr;
	JTextField tsup;
	JTextField tsupr;
	

	JButton sub,run,hang,;
	DefaultListModel mr,mw,ms,mh;
	JList jlr,jlw,jls,jlh;
	
	
	String [] sItem = {"随机算法"};
	Queue queue = new Queue(this);
	RunThread rt;
	Pcb phang = null;
	public int xRes = 10;
	public int xaRes = 10;
	
	public Tu() {
		super("进程模拟程序");
		c = getContentPane();
		c.setLayout(new BorderLayout(1,2));
		jmb = new JMenuBar();
		jm = new JMenu("打开");
		sl = new JMenuItem("示例运行");
		p1 = new JPanel();
		p2 = Box.createVerticalBox();
		p4t1 = Box.createVerticalBox();
		p5t1 = Box.createVerticalBox();
		Box.createVerticalStrut(2);
		p1t1 = new JPanel();
		p3 = new JPanel();
		p3s = new JPanel();
		p3st1 = new JPanel();
		p3t1 = new JPanel();
		p3t2 = new JPanel();
		p4 = new JPanel();
		p5 = new JPanel();
		pg = new JPanel();
		p1t1.setLayout(new FlowLayout(FlowLayout.LEFT));
		p1.setLayout(new BorderLayout(1,2));
		p3.setLayout(new BorderLayout(1,2));
		p3s.setLayout(new BorderLayout(1,2));
		p3st1.setLayout(new FlowLayout(FlowLayout.CENTER));
		p3t1.setLayout(new FlowLayout(FlowLayout.LEFT));
		p3t2.setLayout(new BorderLayout(1,2));
		p4.setLayout(new BorderLayout(1,2));
		p5.setLayout(new BorderLayout(1,2));
		
		cpu = new JLabel("     CPU");
		msg = new JLabel("当前运行的进程");
		pid = new JLabel("PID");
		pidr = new JLabel("     PID");
		sup = new JLabel("优先级");
		supr = new JLabel("优先级");
		rtime = new JLabel("要求运行时间");
		rtimer = new JLabel("要求运行时间");
		
		jlh = new JList(mh);
		jlh.setBorder(BorderFactory.createTitledBorder("挂起队列"));
		jlh.addListSelectionListener(new ListSelectionListener(){
			public void valueChanged(ListSelectionEvent e) {
				Tu.this.phang = (Pcb)jlh.getSelectedValue();
				jlhang = (JList) e.getSource();
			}
			
		});
		
		
		p1t1.add(pid);
		p1t1.add(tpid);
		p1t1.add(sup);
		p1t1.add(tsup);
		p1t1.add(rtime);
		p1t1.add(trtime);
		
		p1.add(p1t1,BorderLayout.NORTH);
		p1.add(jpb,BorderLayout.SOUTH);
		p2.add(new JScrollPane(jlr));
		
		p3t1.add(add);
		p3t1.add(tadd);
		p3t1.add(rtimer);
		p3t1.add(trtimer);
		p3t1.add(select);	
		
		jm.add(sl);
		jmb.add(jm);
		sl.addActionListener(new ActionListener(){		//读入示例运行文件
			public void actionPerformed(ActionEvent e) {
				Example ex = new Example(Tu.this);
				try {
					queue.getvSupport().addAll(ex.vExaple());
					queue.sortAsSuper(queue.getvSupport());
					PrintList(queue.getvSupport(), ms);
				} catch (IOException e1) {
					System.out.println("文件错误！");
				}
			}			
		});
	
	
			
	public static void main(String [] args){			
	    try {
            UIManager.setLookAndFeel(new org.jvnet.substance.SubstanceLookAndFeel());
        } catch (Exception e) {
            System.err.println("Something went wrong!");
        }
		new Tu();
	}
}