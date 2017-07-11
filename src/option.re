

let map f opt => switch opt {
  | None => None
  | Some x => Some (f x)
};

let chain f opt => switch opt {
  | None => None
  | Some x => (f x)
};

let withDefault defaultValue opt => switch (opt) {
| Some x => x
| None => defaultValue
};