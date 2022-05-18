import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        //Um grafo é uma coleção de vértices e arestas.
        int quantidadeDeVertices = scanner.nextInt();
        //Uma aresta é uma conexão entre dois vértices.
        int quantidadeDeArestas = scanner.nextInt();

        //Criando os arrays de vertices e arestas
        Character[] vertices = new Character[quantidadeDeVertices];
        Aresta[] arestas = new Aresta[quantidadeDeArestas];

        for (int i = 0; i < quantidadeDeVertices; i++) {
            vertices[i] = scanner.next().charAt(0);
        }

        for (int i = 0; i < quantidadeDeArestas; i++) {
            String item =  scanner.next();
            int value = scanner.nextInt();
            arestas[i] = new Aresta(value, item.substring(0, 2));
        }

        GrafoMatrizDeAdjacencia grafoMatrizDeAdjacencia = new GrafoMatrizDeAdjacencia(vertices, arestas);
        GrafoListaDeAdjacencia grafoListaDeAdjacencia = new GrafoListaDeAdjacencia(vertices, arestas);
        System.out.println("Grafo com matriz de Adjacência: ");
        System.out.println(grafoMatrizDeAdjacencia);
        System.out.println("Grafo com lista de adjacências: ");
        System.out.println(grafoListaDeAdjacencia);
        System.out.println("Grafo com matriz de Adjacência: \n");
        grafoMatrizDeAdjacencia.BFS('S');
        System.out.println("Grafo com lista de adjacências: \n");
        //grafoListaDeAdjacencia.DFS();
    }
}