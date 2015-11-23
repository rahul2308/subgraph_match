import java.util.*;
import java.util.Vector;
import java.io.*;
public class vertex {
	private int token;  			//name of vertex
	
	public Vector<Integer>  connected = new Vector<Integer>();		//vector containing all vertex cconnected to it
	
	public Vector<Integer>  properties = new Vector<Integer>();		//list of properties of vertex


	public vertex (int token ,Vector<Integer> conn,Vector<Integer> prop) {
		this.token=token; 

		for (int i=0; i<conn.size();i++ )
			connected.addElement (conn.get(i));

		for (int i=0;i<prop.size() ;i++ ) 		
			properties.addElement(prop.get(i));
	}

	public vertex () {
		this.token=0;
	}

	public Vector<Integer> getConnection() {
		return connected;
	}

	public Vector<Integer> getProperties() {
		return properties;
	}
}