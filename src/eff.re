open Data;
type t = option (Task.t action action);
let none = None;
let flip f a b => f b a;

let dummySession = {
      token: "", 
        user: {
          email: "andreas@sentia.io", 
          forenames: "Andreas", 
          lastname: "Møller"
        }
    };
let login ({email, password}:loginForm) => {
  let query = "
    query Authenticate($email: String!, $password:String!) {
      authenticate(email: $email, password:$password) {
        token,
        user {
          id,
          email,
          forenames,
          lastname
          dealership {
            id,
            name
          }
        }
      }
    }
  ";
  let variables = {
    "email": email,
    "password": password
  };

  let decodeSession = Util.decode (Json.Decode.at ["data", "authenticate"] Data.sessionDecoder);
  Some (GraphQL.request query variables
    |> Task.map (fun x => {Js.log2 "RES" x; x})
    |> Task.map decodeSession
    |> Task.chain Task.fromResult
    |> Task.chain (fun sess => {
        AsyncStorage.setItem "jwt" sess.token
          |> Task.map (fun _ => sess);
    })
    |> Task.biMap (fun err => LoginError err) (fun ok => LoginSuccess ok)
  );
};


