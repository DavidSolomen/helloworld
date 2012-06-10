import java.util.Vector;

public class CheckSafe {
	private int work;
	Tu t;
	private Vector<Integer> vtestres, vtesthres;

	public CheckSafe(Tu t) {
		this.t = t;
		work = t.xaRes;
		vtestres = new Vector<Integer>();
		vtesthres = new Vector<Integer>();
		for (int i = 0; i < t.queue.getvReady().size(); i++) {
			vtestres.add(t.queue.getvReady().get(i).getres());
			vtesthres.add(t.queue.getvReady().get(i).gethres());
		}
		for (int i = 0; i < t.queue.getvWait().size(); i++) {
			vtestres.add(t.queue.getvWait().get(i).getres());
			vtesthres.add(t.queue.getvWait().get(i).gethres());
		}
	}


	public boolean test() {
		if (t.cscontrol == true) {
			int count = 0;
			int flag = vtestres.size();
			a: while (vtestres.size() != 0) {
				count++;
				for (int i = 0; i < vtestres.size(); i++) {
					if (vtestres.get(i) <= work) {
						work += vtesthres.get(i);
						vtestres.remove(i);
						vtesthres.remove(i);
						break;
					}
				}
				if (count > flag)
					break a;
			}
			if (vtestres.size() == 0)
				return true;
			else
				return false;
		} else
			return true;
	}
}
