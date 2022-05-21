import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        Character[] vertices;
        Aresta[] arestas;

        try {
            try (BufferedReader br = new BufferedReader(new FileReader("in/1.txt"))) {
                String line = br.readLine();
                Scanner scan = new Scanner(line);

                int quantidadeDeVertices = scan.nextInt();
                int quantidadeDeArestas = scan.nextInt();

                vertices = new Character[quantidadeDeVertices];
                arestas = new Aresta[quantidadeDeArestas];

                for (int i = 0; i < quantidadeDeVertices; i++) {
                    line = br.readLine();
                    vertices[i] = line.charAt(0);
                }

                for (int i = 0; i < quantidadeDeArestas; i++) {
                    line = br.readLine();
                    Scanner scanTemp = new Scanner(line);
                    String item =  scanTemp.next();
                    int value = scanTemp.nextInt();
                    arestas[i] = new Aresta(value, item.charAt(0), item.charAt(1));
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        try{
            GrafoMatrizDeAdjacencia grafoMatrizDeAdjacencia = new GrafoMatrizDeAdjacencia(vertices, arestas);
            GrafoListaDeAdjacencia grafoListaDeAdjacencia = new GrafoListaDeAdjacencia(vertices, arestas);
            System.out.println("Grafo com matriz de adjacência: ");
            System.out.println(grafoMatrizDeAdjacencia);
            System.out.println("Grafo com lista de adjacência: ");
            System.out.println(grafoListaDeAdjacencia);

            System.out.print("Vértice de partida: ");
            grafoMatrizDeAdjacencia.MST_PRIM(scanner.next().charAt(0));
            grafoListaDeAdjacencia.MST_KRUSKAL();
        } catch (NoSuchFieldException e) {
            System.out.println(e.getMessage());
        }
    }
}