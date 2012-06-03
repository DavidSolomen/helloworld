z
class CpuRun extends Thread {
	private int rtime;
	private int htime;
	private int value1,value2;
	private int sup;
	private boolean bl;
	Tu t;
	Pcb p;

	public CpuRun(Tu t, Pcb p) {
		this.t = t;
		this.p = p;
		rtime = p.getrtime();
		htime = p.gethtime();
		sup = p.getsup();
		sup--;
		value1 = 100;
		
	}

	public void run() { // 处理正在运行的进程
		while (bl&&t.crcontrol) {
			if (rtime > 80) {
				rtime -= 80;
				htime += 80;
			} else {
				rtime = 0;
				htime += rtime;
			}
			p.setrtime(rtime);
			p.sethtime(htime);
			p.setsup(sup);
			
			t.tpidr.setText(p.getPID());
			t.tsupr.setText(p.getsup()+"");
			t.thresr.setText(p.gethres()+"");
			value1 = (rtime*100/(rtime+htime));
			t.jpbr.setValue(value1);
			
			try {
				Thread.sleep(80);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			
		}
	}
}