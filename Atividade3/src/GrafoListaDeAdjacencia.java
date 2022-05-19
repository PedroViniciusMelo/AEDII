import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;

public class GrafoListaDeAdjacencia {

    public final LinkedList<Character> vertices;
    public final LinkedList<Aresta>[] listaDeAdjacencia;
    public final int quantidadeDeVertices;

    int clock;

    public enum cores {
        BRANCO,
        PRETO,
        CINZA
    }

    cores[] cor;

    Character[] parents;

    Integer[] descoberta;

    Integer[] distanciaFinal;

    class Conjunto {
        String parent;
        int index;


        public Conjunto(String parent, int index){
            this.parent = parent;
            this.index = index;
        }

        @Override
        public boolean equals(Object o) {
            if (o == this) {
                return true;
            }

            if (!(o instanceof Conjunto)) {
                return false;
            }

            Conjunto conjunto = (Conjunto) o;

            return this.parent.equals(conjunto.parent);
        }

        @Override
        public String toString(){
            return this.parent + " [" + index + "]" ;
        }

    }

    public GrafoListaDeAdjacencia(Character[] vertices, Aresta[] arestas) {
        this.vertices = new LinkedList<>(List.of(vertices));
        quantidadeDeVertices = this.vertices.size();

        listaDeAdjacencia = new LinkedList[quantidadeDeVertices];
        for (int i = 0; i < quantidadeDeVertices; i++) {
            listaDeAdjacencia[i] = new LinkedList<>();
        }

        for (Aresta aresta : arestas) {
            int indiceVertice1 = this.vertices.indexOf(aresta.vertice1);
            int indiceVertice2 = this.vertices.indexOf(aresta.vertice2);

            listaDeAdjacencia[indiceVertice1].add(new Aresta(aresta.peso, aresta.vertice1, aresta.vertice2));
            listaDeAdjacencia[indiceVertice2].add(new Aresta(aresta.peso, aresta.vertice2, aresta.vertice1));
        }
    }
    Conjunto find(Conjunto[] conjuntos, Character vertice) {
        for (Conjunto conjunto : conjuntos) {
            if(conjunto != null && conjunto.parent.contains(vertice.toString())){
                return conjunto;
            }
        }
        return null;
    }

    void Union(Conjunto[] subsets, Conjunto x, Conjunto y) {
        Conjunto uniao = new Conjunto(x.parent + y.parent, 0);

        uniao.index = y.index;
        subsets[y.index] = uniao;
        subsets[x.index] = null;
    }


    public void MST_KRUSKAL(){
        Conjunto[] conjuntos = new Conjunto[quantidadeDeVertices];
        LinkedList<Aresta> holdArestas = new LinkedList<Aresta>();
        Aresta[] resultado = new Aresta[quantidadeDeVertices];

        int count = 0;
        for (Character item: vertices) {
            conjuntos[count] = new Conjunto(item.toString(), count);
            count++;
        }

        for (LinkedList<Aresta> hold : this.listaDeAdjacencia) {
            for (Aresta aresta : hold){
                if(!holdArestas.contains(aresta)){
                    holdArestas.add(aresta);
                }
            }
        }

        Collections.sort(holdArestas);

        for (int i = 0; i < quantidadeDeVertices; i++){
            Aresta proximaAresta = holdArestas.get(i);

            Conjunto x = find(conjuntos, proximaAresta.vertice1);
            Conjunto y = find(conjuntos, proximaAresta.vertice2);

            if (!x.equals(y)) {
                resultado[i] = proximaAresta;
                Union(conjuntos, x, y);
            }
        }
        System.out.println(Arrays.toString(conjuntos));

        for (Aresta item :
                resultado) {
            if(item != null){
                System.out.println(item.vertice1 +""+ item.vertice2);
            }
        }

    }

    /*public void DFS(){
        this.cor = new cores[this.quantidadeDeVertices];
        this.parents = new Character[this.quantidadeDeVertices];
        this.descoberta = new Integer[this.quantidadeDeVertices];
        this.distanciaFinal = new Integer[this.quantidadeDeVertices];

        int hold = 0;
        for (char item: this.vertices) {
            this.cor[hold] = cores.BRANCO;
            this.parents[hold] = null;
            this.descoberta[hold] = 0;
            this.distanciaFinal[hold] = 0;
            hold++;
        }

        this.clock = 0;

        for (char item : this.vertices) {
            int u = this.vertices.indexOf(item);
            if(cor[u].equals(cores.BRANCO)){
                DFS_VISIT(u);
            }
        }

        printItems();
    }*/

    /*private void DFS_VISIT(int u) {
        this.cor[u] = cores.CINZA;
        this.clock++;
        this.descoberta[u] = this.clock;

        for (int v : this.listaDeAdjacencia[u]){
            if(cor[v].equals(cores.BRANCO)){
                this.parents[v] = this.vertices.get(u);
                DFS_VISIT(v);
            }
        }
        cor[u] = cores.PRETO;

        distanciaFinal[u] = ++this.clock;
    }*/

    void printItems(){
        System.out.println("Cores: " + Arrays.toString(this.cor));
        System.out.println("Distâncias: " + Arrays.toString(this.descoberta));
        System.out.println("Predencessores: " + Arrays.toString(this.parents));
        System.out.println("Tempo final: " + Arrays.toString(this.distanciaFinal));
    }

   @Override
    public String toString() {
        StringBuilder graph = new StringBuilder();

        for (int i = 0; i < quantidadeDeVertices; i++) {
            graph.append(vertices.get(i))
                    .append(": ");
            LinkedList<Aresta> linkedList = listaDeAdjacencia[i];
            for (Aresta index : linkedList) {
                graph.append(" ").append(index).append('\t')
                ;
            }
            graph.append("\n");
        }

        return graph.toString();
    }
}