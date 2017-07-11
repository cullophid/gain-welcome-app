let decode decoder json => {
  open Result;
  try (Ok (json |> decoder)) {
  | Js.Exn.Error err => Error (Js.Exn.message err |> Option.withDefault "Could not parse JSON")
  | Json_decode.DecodeError err => Error err
  }
};
