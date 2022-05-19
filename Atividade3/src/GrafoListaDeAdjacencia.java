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
        LinkedList<Aresta> arestas = new LinkedList<Aresta>();
        LinkedList<Aresta> resultado = new LinkedList<Aresta>();

        int count = 0;
        for (Character item: vertices) {
            conjuntos[count] = new Conjunto(item.toString(), count);
            count++;
        }

        for (LinkedList<Aresta> hold : this.listaDeAdjacencia) {
            for (Aresta aresta : hold){
                if(!arestas.contains(aresta)){
                    arestas.add(aresta);
                }
            }
        }

        Collections.sort(arestas);

        for (int i = 0, e = 0; i < arestas.size(); i++, e++){
            Aresta proximaAresta = arestas.get(i);

            Conjunto x = find(conjuntos, proximaAresta.vertice1);
            Conjunto y = find(conjuntos, proximaAresta.vertice2);

            if (!x.equals(y)) {
                resultado.add(proximaAresta);
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