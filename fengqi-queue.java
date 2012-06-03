import java.util.*;

public class Queue {
	private Vector<Pcb> vReady;          //继续队列

	private Vector<Pcb> vWait;			//等待队列

	private Vector<Pcb> vSupport;		//后备队列

	private Vector<Pcb> vHang;			//挂起队列

	private List<Store> lstore;
	private ListIterator<Store> listore;

	Pcb p = null;
	Pcb p1;
	Tu t;
	CheckSafe cs;

	public Queue(Tu t) {
		vReady = new Vector<Pcb>();
		vSupport = new Vector<Pcb>();
		vWait = new Vector<Pcb>();
		vHang = new Vector<Pcb>();
		lstore = Collections.synchronizedList(new ArrayList<Store>());
		initialize();
		this.t = t;
	}

	public Vector<Pcb> getvWait() {
		return vWait;
	}

	public Vector<Pcb> getvReady() {
		return vReady;
	}

	public Vector<Pcb> getvSupport() {
		return vSupport;
	}

	public Vector<Pcb> getvHang() {
		return vHang;
	}

	public void initialize() { // 初始化内存
		Store s = new Store();
		s.setnum(0);
		s.setlength(100);
		s.setaddress(0);
		s.setuse(true);
		lstore.add(s);
	}

	

	public void readyToWait(Pcb p) {
		if (vReady.size() > 0) {
			vWait.add(p);
			vReady.remove(p);
			sortAsSuper(vWait);
		}
	}

	public void waitToReady(Pcb p) {
		if (vWait.size() > 0) {
			vReady.add(p);
			vWait.remove(p);
			sortAsSuper(vReady);
		}
	}

	public void toHang(Vector<Pcb> v, Pcb p) {
		t.xaRes += p.gethres(); // 释放资源
		// 释放内存
		freeStore(p);
		p.sethres(0);
		p.setres(p.getares() - 0);
		vHang.add(p);
		v.remove(p);
		PaintStore ps = new PaintStore();
		ps.drawStore(t);
		t.PrintList(vSupport, t.ms);
		t.PrintList(vReady, t.mr);
		t.PrintList(vHang, t.mh);
	}



	public boolean getStore(Pcb p) {
		listore = lstore.listIterator();
		boolean bl = false;
		while (listore.hasNext()) {
			Store s = listore.next();
			if (s.getuse() && s.getlength() >= p.getrstore()) {
				s.setuse(false);

				p.setstoreadd(s.getaddress());
				Store snew = new Store();
				snew.setnum(s.getnum() + 1);
				snew.setaddress(s.getaddress() + p.getrstore());
				snew.setlength(s.getlength() - p.getrstore());
				snew.setuse(true);
				s.setlength(p.getrstore());
				listore.add(snew);
				bl = true;
				t.rt.drawControl = true;
				t.astore -= p.getrstore();
				break;
			}
		}
		return bl;
	}

	