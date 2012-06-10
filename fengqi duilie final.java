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

	public void sortAsSuper(Vector<Pcb> v1) {
		Comparator<Pcb> comp = new SortAsSuper();
		Collections.sort(v1, comp);
	}

	public void supportToReady() {
		while ((vReady.size() + vWait.size() + vHang.size()) < 4
				&& vSupport.size() > 0) {
			// 从后备队列到就绪队列

			if (getStore(vSupport.firstElement())) {
				p1 = vSupport.firstElement();
				p1.giveRequest();
				vReady.add(p1);
				sortAsSuper(vReady);
				vSupport.remove(0);
			} else
				break;
		}

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

	public void reHang(Pcb p) {
		getStore(p);
		vReady.add(p);
		vHang.remove(p);
		t.PrintList(vReady, t.mr);
		t.PrintList(vSupport, t.ms);
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

	public void freeStore(Pcb p) {
		listore = lstore.listIterator();
		boolean bl2 = false;
		Store sPcb = null;
		while (listore.hasNext()) {
			Store s = listore.next();
			Store sup, slow;
			if (p.getstoreadd() == s.getaddress()) {
				sPcb = s;

				listore.previous();
				if (listore.hasPrevious()) { // 释放内存与前拼接
					sup = listore.previous();
					if (sup.getuse()) {
						sup.setlength(sup.getlength() + s.getlength());
						bl2 = true;
						listore.next();
						listore.next();
						listore.remove();
					} else {
						listore.next();
						listore.next();
					}
				} else
					listore.next();
				sup = s;
				if (listore.hasNext()) { // 释放内存与后拼接
					slow = listore.next();
					if (slow.getuse()) {
						sup.setlength(sup.getlength() + slow.getlength());
						sup.setuse(true);
						listore.previous();
						listore.remove();
						bl2 = true;
					}
				}
				break;
			}
		}

		if (!bl2) {
			listore = lstore.listIterator();
			Store s;
			boolean bl = true;
			while (listore.hasNext()) {
				s = listore.next();
				if (s.getuse()) {
					listore.previous();
					sPcb.setuse(true);
					listore.add(sPcb);
					lstore.remove(sPcb);
					bl = false;
					break;
				}
			}
			if (bl) {
				sPcb.setuse(true);
				lstore.add(sPcb);
				lstore.remove(sPcb);
			}
		}
		t.rt.drawControl = true;
		t.astore += p.getrstore();
	}
}

class SortAsSuper implements Comparator<Pcb> { // 按优先级排序
	public int compare(Pcb p1, Pcb p2) {
		Integer a = p1.getsup();
		Integer b = p2.getsup();
		if (a > b) {
			return -1;
		} else if (a < b) {
			return 1;
		} else {
			return 0;
		}
	}

}
