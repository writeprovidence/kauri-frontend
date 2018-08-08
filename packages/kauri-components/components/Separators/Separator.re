let component = ReasonReact.statelessComponent("HorizontalSeparator");

module Styles = {
  let horizontal = Css.[height(px(2)), width(`percent(100.0))];

  let vertical = Css.[width(px(2)), height(`percent(100.0))];

  let whiteColor = [Css.background(Css.hex("F2F2F2"))];
  let lightGrayColor = [Css.background(Css.hex("EBEBEB"))];
  let getMarginStyle = my =>
    switch (my) {
    | Some(my) => Css.[marginTop(px(my)), marginBottom(px(my))]
    | None => Css.[marginTop(px(10)), marginBottom(px(10))]
    };
};

let getDirectionStyle = d =>
  switch (d) {
  | "horizontal" => Styles.horizontal
  | "vertical" => Styles.vertical
  | _ => Styles.horizontal
  };

type color =
  | LightGray
  | White;

let getColorStyle = color =>
  switch (color) {
  | LightGray => Styles.lightGrayColor
  | White => Styles.whiteColor
  };

let make = (~direction, ~color=White, ~my=?, _children) => {
  ...component, /* spread the template's other defaults into here  */
  render: _self => {
    let directionStyle = getDirectionStyle(direction);
    let colorStyle = getColorStyle(color);
    let marginStyle = Styles.getMarginStyle(my);
    let separatedStyles =
      List.concat([colorStyle, directionStyle, marginStyle]) |. Css.style;
    <div className=separatedStyles />;
  },
};