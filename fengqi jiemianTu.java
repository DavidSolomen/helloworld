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
	JLabel rs;
	JLabel add;
	JLabel cpu;
	JLabel msg;
	JLabel rres;
	JLabel select;
	JLabel rstore;

	JTextField tpid;
	JTextField tpidr;
	JTextField tsup;
	JTextField tsupr;
	JTextField trtime;
	JTextField trtimer;
	JTextField tares;
	JTextField thresr;
	JTextField trs;
	JTextField tadd;
	JTextField trres;
	JTextField trstore;

	JButton sub,run,hang,rhang,hangr;
	DefaultListModel mr,mw,ms,mh;
	JList jlr,jlw,jls,jlh;
	JComboBox jcb;
	JProgressBar jpb,jpbv,jpbr;
	
	String [] sItem = {"���м��㷨","����㷨"};
	Queue queue = new Queue(this);
	RunThread rt;
	Pcb phang = null;
	JList jlhang;
	boolean crcontrol,cscontrol;
	public int xRes = 10;
	public int xaRes = 10;
	public int timeslice = 4000;
	public int astore = 100;

	public Tu() {
		super("����ģ�����");
		c = getContentPane();
		c.setLayout(new BorderLayout(1,2));
		jmb = new JMenuBar();
		jm = new JMenu("��");
		sl = new JMenuItem("ʾ������");
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
		msg = new JLabel("��ǰ���еĽ���");
		pid = new JLabel("PID");
		pidr = new JLabel("     PID");
		sup = new JLabel("���ȼ�");
		supr = new JLabel("���ȼ�");
		rtime = new JLabel("Ҫ������ʱ��");
		rtimer = new JLabel("Ҫ������ʱ��");
		ares = new JLabel("��Դ��������");
		hresr = new JLabel("��ռ����Դ");
		rs = new JLabel("��������");
		add = new JLabel("�����ַ");
		rres = new JLabel("ʣ����Դ");
		select = new JLabel("��Դ�����㷨");
		rstore = new JLabel("����ʣ��");
		tpid = new JTextField(6);
		tpidr = new JTextField(10);
		tsup = new JTextField(3);
		tsupr = new JTextField(5);
		trtime = new JTextField(7);
		trtimer = new JTextField(10);
		tares = new JTextField(3);
		thresr = new JTextField(5);
		trs = new JTextField(3);
		tadd = new JTextField(5);
		trres = new JTextField();
		trstore = new JTextField();
		sub = new JButton("�ύ");
		run = new JButton("����");
		hang = new JButton("����");
		rhang = new JButton("���");
		hangr = new JButton("����ǰ����");
		mr = new DefaultListModel();
		mw = new DefaultListModel();
		ms = new DefaultListModel();
		mh = new DefaultListModel();
		jlr = new JList(mr);
		jlr.setBorder(BorderFactory.createTitledBorder("��������"));
		jlr.addListSelectionListener(new ListSelectionListener(){
			public void valueChanged(ListSelectionEvent e) {
				Tu.this.phang = (Pcb) jlr.getSelectedValue();
				jlhang = (JList) e.getSource();
			}
		});
		jlw = new JList(mw);		
		jlw.setBorder(BorderFactory.createTitledBorder("�ȴ�����"));
		jls = new JList(ms);
		jls.setBorder(BorderFactory.createTitledBorder("�󱸶���"));
		jls.addListSelectionListener(new ListSelectionListener(){
			public void valueChanged(ListSelectionEvent e) {
				Tu.this.phang = (Pcb)jls.getSelectedValue();
				jlhang = (JList) e.getSource();
			}
			
		});
		jlh = new JList(mh);
		jlh.setBorder(BorderFactory.createTitledBorder("�������"));
		jlh.addListSelectionListener(new ListSelectionListener(){
			public void valueChanged(ListSelectionEvent e) {
				Tu.this.phang = (Pcb)jlh.getSelectedValue();
				jlhang = (JList) e.getSource();
			}
			
		});
		
		jcb = new JComboBox();
		for(int i=0;i<sItem.length;i++)
			jcb.addItem(sItem[i]);
		jcb.addItemListener(new ItemHandle());
		sub.addActionListener(new BHandle());
		run.addActionListener(new BHandle());
		hang.addActionListener(new BHandle());
		rhang.addActionListener(new BHandle());
		hangr.addActionListener(new BHandle());
//		setres.addActionListener(new BHandle());
		jpb = new JProgressBar(0,100);
		jpbv = new JProgressBar(SwingConstants.VERTICAL,0,100);
		jpbr = new JProgressBar(0,100);
		jpbr.setValue(100);
		jpb.setString("ʱ��Ƭ����");
		jpb.setStringPainted(true);
		jpbv.setString("ʣ����Դ��");
		jpbv.setStringPainted(true);
		jpbr.setString("Ҫ������ʱ��");
		jpbr.setStringPainted(true);
		
		p1t1.add(pid);
		p1t1.add(tpid);
		p1t1.add(sup);
		p1t1.add(tsup);
		p1t1.add(rtime);
		p1t1.add(trtime);
		p1t1.add(ares);
		p1t1.add(tares);
		p1t1.add(rs);
		p1t1.add(trs);
		p1t1.add(sub);
		p1t1.add(run);
		p1t1.add(hang);
		p1t1.add(rhang);
		p1.add(p1t1,BorderLayout.NORTH);
		p1.add(jpb,BorderLayout.SOUTH);
		p2.add(new JScrollPane(jlr));
		p2.add(new JScrollPane(jls));
		p2.add(new JScrollPane(jlw));
		p2.add(new JScrollPane(jlh));
		p3t1.add(pidr);
		p3t1.add(tpidr);
		p3t1.add(supr);
		p3t1.add(tsupr);
		p3t1.add(hresr);
		p3t1.add(thresr);
		p3t1.add(add);
		p3t1.add(tadd);
		p3t1.add(rtimer);
		p3t1.add(trtimer);
		p3t1.add(select);	
		p3t1.add(jcb);
		p3st1.add(msg);
		p3s.add(p3t1,BorderLayout.CENTER);
		p3s.add(p3st1,BorderLayout.NORTH);
		p3t2.add(cpu,BorderLayout.WEST);
		p3t2.add(jpbr,BorderLayout.CENTER);
		p3t2.add(hangr,BorderLayout.EAST);
		p3.add(p3t2,BorderLayout.SOUTH);
		p3.add(p3s,BorderLayout.CENTER);
		p4t1.add(rres);
		p4t1.add(trres);
		p4.add(jpbv,BorderLayout.CENTER);
		p4.add(p4t1,BorderLayout.SOUTH);
		p5t1.add(rstore);
		p5t1.add(trstore);
		p5.add(pg,BorderLayout.CENTER);
		p5.add(p5t1,BorderLayout.SOUTH);
		jm.add(sl);
		jmb.add(jm);
		sl.addActionListener(new ActionListener(){		//����ʾ�������ļ�
			public void actionPerformed(ActionEvent e) {
				Example ex = new Example(Tu.this);
				try {
					queue.getvSupport().addAll(ex.vExaple());
					queue.sortAsSuper(queue.getvSupport());
					PrintList(queue.getvSupport(), ms);
				} catch (IOException e1) {
					System.out.println("�ļ�����");
				}
			}			
		});
		
		setJMenuBar(jmb);
		c.add(p3,BorderLayout.NORTH);
		c.add(p2, BorderLayout.CENTER);
		c.add(p1,BorderLayout.SOUTH);
		c.add(p4,BorderLayout.EAST);
		c.add(p5,BorderLayout.WEST);

		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(800, 580);
		setVisible(true);
		this.addWindowListener(new WindowAdapter(){			//������ģ������ػ�
			PaintStore ps = new PaintStore();
			public void windowActivated(WindowEvent e) {
				ps.drawStore(Tu.this);
			}

			public void windowDeiconified(WindowEvent e) {
				ps.drawStore(Tu.this);
			}
			
			public void windowOpened(WindowEvent e){
				tpid.requestFocus();
			}
		});
		
		crcontrol = true;
		cscontrol = true;
	}

	class ItemHandle implements ItemListener{			//ѡ�����м�����㷨
		public void itemStateChanged(ItemEvent e) {
			String s = (String)e.getItem();
			if(s!="���м��㷨")
				cscontrol = false;
			else
				cscontrol = true;
		}
		
	}
	
	class BHandle implements ActionListener{

		public void actionPerformed(ActionEvent ae) {
			Pcb p;
			if(ae.getActionCommand()=="�ύ"){
				p = new Pcb(Tu.this);
				queue.getvSupport().add(p);
				queue.sortAsSuper(queue.getvSupport());
				PrintList(queue.getvSupport(),ms);
				clearSubit();
			}
			if(ae.getActionCommand()=="����"){				//����ʼ����		
				rt = new RunThread(Tu.this);
				rt.start();
			}
			if(ae.getActionCommand()=="����"){
				if(jlhang==jlr){
					queue.toHang(queue.getvReady(), phang);		//�������
				}
				if(jlhang==jls){
					queue.toHang(queue.getvSupport(), phang);
				}
				else{

				}
			}
			if(ae.getActionCommand()=="���"){					//��ҽ���
				if(jlhang==jlh){
					queue.reHang(phang);
					for(int i=1;i<queue.getvReady().size();i++)
						mr.addElement(queue.getvReady().get(i));
					PrintList(queue.getvHang(), mh);
				}
				else{

				}
			}
			if(ae.getActionCommand()=="����ǰ����"){				//����ǰ����
				crcontrol = false;
				queue.toHang(queue.getvReady(), queue.getvReady().firstElement());
				PrintList(queue.getvSupport(), ms);
				PrintList(queue.getvReady(), mr);
				PrintList(queue.getvHang(), mh);
			}
		}
	}
	public void clearSubit(){
		tpid.setText("");
		tsup.setText("");
		trtime.setText("");
		tares.setText("");
		trs.setText("");
	}
	
	
	public void PrintList(Vector<Pcb> v, DefaultListModel d) {
		d.clear();
		for (int i = 0; i < v.size(); i++) {
			d.addElement(v.elementAt(i));
		}
	}		
	public static void main(String [] args){			
	    try {
            UIManager.setLookAndFeel(new org.jvnet.substance.SubstanceLookAndFeel());
        } catch (Exception e) {
            System.err.println("Something went wrong!");
        }
		new Tu();
	}
}