let game,
    state = 0,
    selector = {
        Start: $("#Start"),
        Back: $("#Back"),
        Next: $("#Next"),
        Walk: $("#Next, #Start"),
        Sdominance: $("#Sdominance"),
        Wdominance: $("#Wdominance"),
        IESDS: $("#IESDS"),
        Nequilibrium: $("#Nequilibrium"),
        Pequilibrium: $("#Pequilibrium"),
        Descriptions: {
            body: $(".DescriptionBody"),
            Desc: $('[name="Description"]'),
            PlayerNumber: $('[name="Number"]'),
            Button: $("#SelectNumber"),
            back: $("#backGame"),
        },
        Strategies: {
            body: $(".StrategiesBody"),
            main: $("#StrategiesBody"),
        },
        Table: {
            body: $(".Table"),
            Table: $(".Table table"),
            description: $(".Table p"),
        },
    },
    data = {};

function init() {
    hide(selector.Descriptions.body);
    hide(selector.Strategies.body);
    hide(selector.Table.body);
    hide(selector.Back);
    hideShow(selector.Start, selector.Next);
}
class Player {
    Strategies = [];
    order;
    constructor(order, num) {
        this.order = order;
        for (let i = 1; i <= num; i++) {
            this.Strategies.push($(`<input value="S${i}" name="strategieP${order}S${i}">`));
        }
    }
    clone(i) {
        console.log(i);
        let $this = this,
            clone = this.Strategies[i].clone().change(function (e) {
                $(`input[name='strategieP${$this.order}S${i + 1}']`).val($(this).val());
                e.preventDefault();
                return false;
            }),
            div = $(`<div><span>P${this.order} : </span></div>`).append(clone),
            elm = $(`<th></th>`).append(div);
        return elm;
    }
}
class Gains {
    Data;
    List = [];
    constructor(Data) {
        this.Data = Data;

        for (const row of this.Data) {
            for (const col of row) {
                this.List.push(col);
            }
        }
    }
    ClearBoard() {
        this.List.forEach((elm) => elm.td.removeClass("selected"));
    }
    ParetoDominence(data1, data2) {
        console.log(data1, data2);
        let condition = false;
        for (let i = 0; i < data1.length && !condition; i++) {
            let midCondition = true;
            for (let j = 0; j < data1.length && midCondition; j++) {
                if (i == j) midCondition &&= data2[j] >= data1[j];
                else midCondition &&= data2[j] > data1[j];
                console.log(midCondition);
            }
            condition ||= midCondition;
        }
        return condition;
    }
    ParetoEquilibrium() {
        this.ClearBoard();
        let equilibrium = [];
        for (let i = 0; i < this.List.length; i++) {
            let e = true;
            for (let j = 0; j < this.List.length && e; j++) {
                if (i == j) continue;
                e = !this.ParetoDominence(this.List[i].data, this.List[j].data);
            }
            if (e) equilibrium.push(this.List[i]);
        }
        equilibrium.forEach((elm) => elm.td.addClass("selected"));
    }
    StrictDominance() {
        this.ClearBoard();
    }
    WeaklyDominance() {
        this.ClearBoard();
    }
    NeshEquilibrium() {
        this.ClearBoard();
    }
    IESDS() {
        this.ClearBoard();
    }
}

class Game {
    description;
    players;
    width;
    height;
    v;
    h;
    TableSize;
    Table;
    Gains;
    constructor(Table, { description, playersStrategies }) {
        this.description = description;
        this.Table = Table;
        this.players = playersStrategies;
        this.Calculate();
        this.CreateTable();
        Table.description.append(description);
    }
    Calculate() {
        const half = this.players.length / 2;
        this.v = Math.ceil(half);
        this.h = Math.floor(half);
        this.TableSize = [1, 1];
        for (let i = this.players.length - 1; i >= 0; i--) {
            if (i < this.h) {
                this.TableSize[0] *= this.players[i].Strategies.length;
            } else {
                this.TableSize[1] *= this.players[i].Strategies.length;
            }
        }
        this.width = this.h + this.TableSize[1];
        this.height = this.v + this.TableSize[0];
    }
    CreateTable() {
        let thead = $(`<thead></thead>`),
            tbody = $(`<tbody></tbody>`),
            level = 1,
            $this = this,
            Data = [];

        for (let i = this.h; i < this.players.length; i++) {
            let tr = $("<tr></tr>");
            for (let j = 0; j < level; j++) {
                for (const strategie in this.players[i].Strategies) {
                    tr.append(
                        this.players[i]
                            .clone(Number(strategie))
                            .attr(
                                "colspan",
                                this.TableSize[1] / (this.players[i].Strategies.length * level)
                            )
                    );
                }
            }
            thead.append(tr);
            level *= this.players[i].Strategies.length;
        }
        for (let i = 0; i < this.TableSize[0]; i++) {
            let tr = $("<tr></tr>"),
                row = [];
            level = this.TableSize[0];
            for (let k = 0; k < this.h; k++) {
                level /= this.players[k].Strategies.length;

                if (i % level === 0) {
                    tr.append(
                        this.players[k]
                            .clone(
                                Math.floor(i / level) % (level * this.players[k].Strategies.length)
                            )
                            .attr("rowspan", level)
                    );
                }
            }
            for (let k = 0; k < this.TableSize[1]; k++) {
                let div = $("<div>(</div>"),
                    td = $("<td></td>"),
                    col = [];

                for (let l = 0; l < this.players.length; l++) {
                    col[l] = Math.floor(Math.random() * 5);
                    let input = $(
                        `<input name="gain[${i}][${k}][${l}]" type="number" value="${col[l]}">`
                    );
                    div.append(
                        input.change(function (e) {
                            $this.Gains.Data[i][k].data[l] = Number(input.val());
                            e.preventDefault();
                            return false;
                        })
                    );
                    if (l == this.players.length - 1) div.append(")");
                    else div.append(",");
                }

                tr.append(td.append(div));
                row[k] = { data: col, td };
            }
            tbody.append(tr);
            Data[i] = row;
        }
        this.Gains = new Gains(Data);
        thead
            .children()
            .first()
            .prepend(`<th rowspan="${this.v}" colspan="${this.h}">Players</th>`);
        this.Table.Table.empty().append(thead).append(tbody);
        console.log(this);
    }
}
function createStrategiesInput(num) {
    let player = $(`<input type="number" class="Strategies" value="2"/>`);
    selector.Strategies.main.append(`<h2>Player ${num}</h2>`).append(player);
    return player;
}
function hide(elm) {
    elm.attr("hidden", true);
    elm.css("display", "none");
}
function show(elm) {
    elm.attr("hidden", false);
    elm.css("display", "flex");
}
function hideShow(bodyS, bodyH) {
    hide(bodyH);
    show(bodyS);
}
selector.Walk.click(function (e) {
    switch (state) {
        case 0: {
            show(selector.Next);
            show(selector.Back);
            hideShow(selector.Descriptions.body, selector.Start);
            break;
        }
        case 1: {
            data = {
                ...data,
                description: selector.Descriptions.Desc.val(),
                player_numbers: selector.Descriptions.PlayerNumber.val(),
                playersStrategiesInputs: [],
            };
            for (let i = 1; i <= data.player_numbers; i++) {
                data.playersStrategiesInputs.push(createStrategiesInput(i));
            }
            hideShow(selector.Strategies.body, selector.Descriptions.body);
            break;
        }
        case 2: {
            data.playersStrategies = data.playersStrategiesInputs.map(
                (element, i) => new Player(i + 1, Number(element.val()))
            );
            game = new Game(selector.Table, data);
            hideShow(selector.Table.body, selector.Strategies.body);
            hide(selector.Next);
            break;
        }
    }
    state++;
    e.preventDefault();
    return false;
});

selector.Back.click(function (e) {
    state--;
    switch (state) {
        case 0: {
            hide(selector.Back);
            hide(selector.Next);
            hideShow(selector.Start, selector.Descriptions.body);
            break;
        }
        case 1: {
            selector.Strategies.main.empty();
            hideShow(selector.Descriptions.body, selector.Strategies.body);
            break;
        }
        case 2: {
            hideShow(selector.Strategies.body, selector.Table.body);
            show(selector.Next);
            break;
        }
    }

    e.preventDefault();
    return false;
});

selector.Sdominance.click(function (e) {
    game.Gains.StrictDominance();
    e.preventDefault();
    return false;
});

selector.Wdominance.click(function (e) {
    game.Gains.WeaklyDominance();
    e.preventDefault();
    return false;
});

selector.IESDS.click(function (e) {
    game.Gains.IESDS();
    e.preventDefault();
    return false;
});

selector.Nequilibrium.click(function (e) {
    game.Gains.NeshEquilibrium();
    e.preventDefault();
    return false;
});

selector.Pequilibrium.click(function (e) {
    game.Gains.ParetoEquilibrium();
    e.preventDefault();
    return false;
});

init();
