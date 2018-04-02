import java.util.HashMap;
import java.util.Map;
import com.fasterxml.jackson.annotation.JsonAnyGetter;
import com.fasterxml.jackson.annotation.JsonAnySetter;
import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;

@JsonInclude(JsonInclude.Include.NON_NULL)
@JsonPropertyOrder({
        "health",
        "attack",
        "defense",
        "speed"
})
public class Stats {

    @JsonProperty("health")
    private Integer health;
    @JsonProperty("attack")
    private Integer attack;
    @JsonProperty("defense")
    private Integer defense;
    @JsonProperty("speed")
    private Integer speed;
    @JsonIgnore
    private Map<String, Object> additionalProperties = new HashMap<String, Object>();

    @JsonProperty("health")
    public Integer getHealth() {
        return health;
    }

    @JsonProperty("health")
    public void setHealth(Integer health) {
        this.health = health;
    }

    @JsonProperty("attack")
    public Integer getAttack() {
        return attack;
    }

    @JsonProperty("attack")
    public void setAttack(Integer attack) {
        this.attack = attack;
    }

    @JsonProperty("defense")
    public Integer getDefense() {
        return defense;
    }

    @JsonProperty("defense")
    public void setDefense(Integer defense) {
        this.defense = defense;
    }

    @JsonProperty("speed")
    public Integer getSpeed() {
        return speed;
    }

    @JsonProperty("speed")
    public void setSpeed(Integer speed) {
        this.speed = speed;
    }

    @JsonAnyGetter
    public Map<String, Object> getAdditionalProperties() {
        return this.additionalProperties;
    }

    @JsonAnySetter
    public void setAdditionalProperty(String name, Object value) {
        this.additionalProperties.put(name, value);
    }

}