public class Brawler {
    private BrawlerType type;
    private int health;

    public Brawler(BrawlerType type) {
        this.type = type;
        this.health = type.getStats().getHealth();
    }

    public BrawlerType getType() {
        return type;
    }

    public int getHealth() {
        return health;
    }

    public void takeDamage(int damage){
        int health = this.health;
        if(damage < health) {
            health = health - damage;
            this.health = health;
        }else if(damage == health || damage > health){
            this.health = 0;
        }
    }

    public boolean isAlive(){
        if(this.health == 0){
            return false;
        }else {
            return true;
        }
    }
}
