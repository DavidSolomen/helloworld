

public class RunThread extends Thread {
	private boolean bl = true;
	public boolean drawControl;
	Tu t;
	Pcb pRun,p;
	CheckSafe chs;
	PaintStore ps;

	public RunThread(Tu t) {
		this.t = t;
		drawControl = false;
		ps = new PaintStore();
	}

	public void run() {
		while (bl) {  // 处理各个队列的转移
			t.queue.supportToReady();
			if (t.queue.getvReady().size() > 0||t.queue.getvHang().size()>0) {
				p = t.queue.getvReady().get(0);
				if (p.getrtime() <= 0){					//  销毁进程
					t.xaRes += p.gethres();				//释放资源
					t.queue.freeStore(p);				//释放内存
					t.queue.getvReady().remove(p);
					t.queue.supportToReady();
					
					t.trstore.setText(t.astore+"%");
					t.trres.setText(t.xaRes+"");
				}
				t.PrintList(t.queue.getvSupport(), t.ms);
				
				a:while(t.queue.getvReady().size()>0||t.queue.getvWait().size()>0){
					chs = new CheckSafe(t);
					for(int i=0;i<t.queue.getvWait().size();i++){
						p = t.queue.getvWait().get(i);
						if(p.haveRequest()){
							t.xaRes += p.getRequest();//? -?
							p.setres(p.getres()+p.getRequest());
							p.sethres(p.gethres()-p.getRequest());
							t.queue.waitToReady(p);
							i--;
						}
					}
					t.queue.sortAsSuper(t.queue.getvReady());
					pRun = t.queue.getvReady().get(0);
					
					if(pRun.haveRequest()){
						break a;
					}
					else{
						t.queue.readyToWait(pRun);
					}
				}
				
				t.trstore.setText(t.astore+"%");
				t.trres.setText(t.xaRes+"");
				
				t.PrintList(t.queue.getvWait(), t.mw);
				t.mr.clear();
				for (int i=0; i < t.queue.getvReady().size(); i++) {
					t.mr.addElement(t.queue.getvReady().get(i));
				}
				if(drawControl==true){
				ps.drawStore(t);
				drawControl = false;
				}
			}
			
			t.jpbv.setValue(t.xaRes*100/t.xRes);
			
			if (t.queue.getvReady().size() != 0) {
				t.crcontrol = true;
				CpuRun cr = new CpuRun(t, pRun);
				cr.start();
				try {
					cr.join();
				} catch (InterruptedException e) {
					System.out.println("cr启动失败");
				}
			}
			pRun.giveRequest();
			if (t.queue.getvReady().size() == 0&t.queue.getvHang().size()==0) // 停止调度条件
				bl = false;
		}
	}
}