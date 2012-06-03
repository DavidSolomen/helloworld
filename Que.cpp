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
