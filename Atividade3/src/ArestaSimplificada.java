public class ArestaSimplificada implements Comparable<ArestaSimplificada>{
    Character vertice;

    int chave;

    public ArestaSimplificada(Character vertice, int chave) {
        this.vertice = vertice;
        this.chave = chave;
    }

    @Override
    public int compareTo(ArestaSimplificada aresta) {
        return Integer.compare(this.chave, aresta.chave);
    }

    @Override
    public boolean equals(Object o) {
        if (o == this) {
            return true;
        }

        if (!(o instanceof ArestaSimplificada)) {
            return false;
        }

        ArestaSimplificada aresta = (ArestaSimplificada) o;

        return this.vertice == aresta.vertice;
    }
}
