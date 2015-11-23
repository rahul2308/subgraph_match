import java.util.*;
import java.util.Vector;
import java.io.*;
public class sm extends vertex {
	public static void main(String[] args) throws IOException {
		
		Vector<Integer>  conn=new Vector<Integer>();
		Vector<Integer>  prop=new Vector<Integer>();
		int []weight={ 10 ,12, 23, 9, 4 ,1 ,14 ,15 ,-1};
		int no_of_prop=8;
		int k;int m=0;
		Scanner fin=null;
		try {
            fin = new Scanner(new File("datagraph_input.txt"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

		int no_of_vertices = fin.nextInt();
		vertex [] datagraph=new vertex[no_of_vertices+1];			//data graph
		
		for(int i=1; i<=no_of_vertices; i++) {
			int vertex_number = i;
			Integer ele;
			while((ele = fin.nextInt()) != -1) {
				conn.addElement(ele);
			}
			while((ele = fin.nextInt()) != -1) {
				prop.addElement(ele);
			}
			datagraph[vertex_number]=new vertex(vertex_number,conn,prop);
			
			conn.clear();
			prop.clear();
		}
		fin.close();
		try {
            fin = new Scanner(new File("querygraph_input.txt"));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
		int no_of_vertices_in_query_graph = fin.nextInt();
		vertex [] querygraph=new vertex[no_of_vertices_in_query_graph+1];		//query graph
		
		for(int i=1; i<=no_of_vertices_in_query_graph; i++) {
			int vertex_number = i, ele;
			while((ele = fin.nextInt()) != -1) {
				conn.addElement(ele);
			}
			while((ele = fin.nextInt()) != -1) {
				prop.addElement(ele);
			}
			querygraph[vertex_number]=new vertex(vertex_number,conn,prop);
			
			conn.clear();
			prop.clear();
		}
		
		fin.close();
		File file1 = new File("datagraph_output.txt");
      // creates the file
      file1.createNewFile();
      // creates a FileWriter Object
      FileWriter writer = new FileWriter(file1); 
      // Writes the content to the file
    
		//data graph and query graph created
		 //System.out.println("-------datagraph--------");
      	writer.write(new Integer(no_of_vertices).toString()+"\n");
		 for(int i=1;i<=no_of_vertices;i++){
		 	//System.out.print(i+" -> ");
		 	Vector <Integer> v1=datagraph[i].getProperties();
		 	for(int j=0;j<v1.size();j++)
		 		writer.write((v1.get(j)).toString()+" ");

		 		writer.write("-1");
		 		writer.write("\n");
		 }
		 writer.flush();
      	 writer.close();
		//  System.out.println(-1);
		// // System.out.println("--------querygraph-------");
		// for(int i=1;i<=no_of_vertices_in_query_graph;i++){
		//  //	System.out.print(i+" -> ");
		//  	Vector <Integer> v1=querygraph[i].getProperties();
		//  	for(int j=0;j<v1.size();j++)
		//  	System.out.print(v1.get(j)+" ");
		//  	System.out.println(-1);
		//  }


		//  //frequent pattern generation starts

	
	}

	
}