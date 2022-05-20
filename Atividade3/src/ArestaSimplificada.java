public class ArestaSimplificada implements Comparable<ArestaSimplificada>{
    Character aresta;

    int chave;

    public ArestaSimplificada(Character aresta, int chave) {
        this.aresta = aresta;
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

        return this.aresta == aresta.aresta;
    }
}
