import java.io.*;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        Character[] vertices;
        String[] arestas;

        try {
            try (BufferedReader br = new BufferedReader(new FileReader("in/8.txt"))) {
                String line = br.readLine();
                Scanner scan = new Scanner(line);

                int quantidadeDeVertices = scan.nextInt();
                int quantidadeDeArestas = scan.nextInt();

                vertices = new Character[quantidadeDeVertices];
                arestas = new String[quantidadeDeArestas];

                for (int i = 0; i < quantidadeDeVertices; i++) {
                    line = br.readLine();
                    vertices[i] = line.charAt(0);
                }

                for (int i = 0; i < quantidadeDeArestas; i++) {
                    line = br.readLine();
                    arestas[i] = line;
                }

            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        GrafoMatrizDeAdjacencia grafoMatrizDeAdjacencia = new GrafoMatrizDeAdjacencia(vertices, arestas);
        GrafoListaDeAdjacencia grafoListaDeAdjacencia = new GrafoListaDeAdjacencia(vertices, arestas);
        System.out.println("Grafo com matriz de adjacência: ");
        System.out.println(grafoMatrizDeAdjacencia);
        System.out.println("Grafo com lista de adjacência: ");
        System.out.println(grafoListaDeAdjacencia);

        System.out.print("Vértice de partida: ");
        grafoMatrizDeAdjacencia.BFS(scanner.next().strip().charAt(0));
        grafoListaDeAdjacencia.DFS();
    }
}