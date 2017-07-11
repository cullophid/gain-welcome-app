type page = 
  | Login
  | Home
  | VisitorInterests
  | VisitorDetails
  | ThankYou
  ;

let pageEncoder page => {
  open Json.Encode;
  switch page {
  | Login => string "Login"
  | Home => string "Home"
  | VisitorInterests => string "VisitorInterests"
  | VisitorDetails => string "VisitorDetails"
  | ThankYou => string "ThankYou"
  };
};

type loginForm = {
  email: string,
  password: string
};

let emptyLoginForm: loginForm = {email: "", password: ""};

let loginFormEncoder {email, password} => {
  open Json.Encode;
  [
    ("email", string email),
    ("password", string password)
  ] |> Js.Dict.fromList |> object_;
};

type user = {
  email: string,
  forenames: string,
  lastname: string
};
let userDecoder json => {
  open Json.Decode;
  {
    email: json |> field "email" string,
    forenames: json |> field "forenames" string,
    lastname: json |> field "lastname" string,
  }
};
let userEncoder user => {
  open Json.Encode;
  [
    ("email", string user.email),
    ("forenames", string user.forenames),
    ("lastname", string user.lastname)
  ] |> Js.Dict.fromList |> object_;
};

type session = {
  token: string,
  user
};
let sessionEncoder session => {
  open Json.Encode;
  [
    ("token", string session.token),
    ("user", userEncoder session.user)
  ] |> Js.Dict.fromList |> object_;
};

let sessionDecoder json => {
  open Json.Decode;
  {
    token : json|> field "token" string,
    user: json |> field "user" userDecoder
  };
};

type visitorType =
  | NotAsked
  | Private
  | PrivateToBusiness
  | Business
  | Na
  ;
let visitorTypeEncoder visitorType => {
  open Json.Encode;
  switch (visitorType) {
    | NotAsked => string "NotAsked"
    | Private => string "Private"
    | PrivateToBusiness => string "PrivateToBusiness"
    | Business => string "Business"
    | Na => string "N/A"
    };
};

type visitorInterests =
  | NotAsked
  | Browsing
  | Learn
  | Testdrive
  | Financing
  | Buy
  ;
let visitorInterestsEncoder visitorInterests => {
  open Json.Encode;
  switch (visitorInterests) {
  | NotAsked => string "NotAsked"
  | Browsing => string "Browsing"
  | Learn => string "Learn"
  | Testdrive => string "Testdrive"
  | Financing => string "Financing"
  | Buy => string "Buy"
  };
};

type visitorForm = {
  visitorType,
  visitorInterests,
  name: string,
  mobile: string,
  concent: bool
};

let visitorFormEncoder queueForm => {
  open Json.Encode;
  [
    ("visitorType", visitorTypeEncoder queueForm.visitorType),
    ("visitorInterests", visitorInterestsEncoder queueForm.visitorInterests),
    ("name", string queueForm.name),
    ("mobile", string queueForm.mobile),
    ("concent", Js.Boolean.to_js_boolean queueForm.concent |> boolean)
  ] |> Js.Dict.fromList |> object_;
};

let emptyVisitorForm:visitorForm = {
  visitorType: NotAsked,
  visitorInterests: NotAsked,
  name: "",
  mobile: "",
  concent: false
};

type model = {
  session: Remote.t string session,
  page,
  loginForm,
  visitorForm
};

let emptyModel: model = {
  session: NotAsked,
  page: Login,
  loginForm: emptyLoginForm, 
  visitorForm: emptyVisitorForm
};

let modelEncoder model => {
  open Json.Encode;
  [
    ("session", (Remote.encoder string sessionEncoder) model.session),
    ("page", pageEncoder model.page),
    ("loginForm", loginFormEncoder model.loginForm),
    ("visitorForm", visitorFormEncoder model.visitorForm)
  ] |> Js.Dict.fromList |> object_
};

type action =
  | NoOp
  | UpdateLoginForm loginForm
  | Login loginForm
  | LoginSuccess session
  | LoginError string
  | SelectVisitorType visitorType
  | SelectVisitorInterests visitorInterests
  | UpdateVisitorForm visitorForm
  | SubmitVisitorForm visitorForm
  | SubmitVisitorFormError string
  | SubmitVisitorFormSuccess
 ;


let printAction action => {
  let stringify = Js.Json.stringify;
  switch action {
  | NoOp => "NoOp"
  | UpdateLoginForm loginForm => "UpdateLoginForm " ^ (loginForm |> loginFormEncoder |> stringify)
  | LoginSuccess session => "LoginSuccess " ^ (session |> sessionEncoder |> stringify)
  | Login loginForm => "Login " ^ (loginForm |> loginFormEncoder |> stringify)
  | LoginError err => "LoginError " ^ (err |> Json.Encode.string |> stringify)
  | SelectVisitorType visitorType => "SelectVisitorType " ^ (visitorType |> visitorTypeEncoder |> stringify)
  | SelectVisitorInterests visitorInterests => "SelectVisitorInterests " ^ (visitorInterests |> visitorInterestsEncoder |> stringify)
  | UpdateVisitorForm visitorForm => "UpdateVisitorForm " ^ (visitorForm |> visitorFormEncoder |> stringify)
  | SubmitVisitorForm visitorForm => "SubmitVisitorForm " ^ (visitorForm |> visitorFormEncoder |> stringify)
  | SubmitVisitorFormError err => "SubmitQueueFormError " ^ (err |> Json.Encode.string |> stringify)
  | SubmitVisitorFormSuccess => "SubmitQueueFormSuccess"
  };
};
