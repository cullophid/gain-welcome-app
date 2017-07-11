let head list => switch list {
| [] => None
| [a] => Some a
| [a, ..._] => Some a
};
let tail list => switch list {
| [] => None
| [_] => None
| [_, ...a] => Some a
};
