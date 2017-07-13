module Page = {
  type t =
  | Login
  | Home
  | VisitorInterests
  | VisitorDetails
  | ThankYou; 
  let encoder page => {
    open Json.Encode;
    switch page {
    | Login => string "Login"
    | Home => string "Home"
    | VisitorInterests => string "VisitorInterests"
    | VisitorDetails => string "VisitorDetails"
    | ThankYou => string "ThankYou"
    };
  };

};

module LoginForm = {

  type t = {
    email: string,
    password: string
  };

  let empty: t = {email: "", password: ""};

  let encoder {email, password} => {
    open Json.Encode;
    [
      ("email", string email),
      ("password", string password)
    ] |> Js.Dict.fromList |> object_;

  }
};

module User = {

  type t = {
    email: string,
    forenames: string,
    lastname: string
  };

  let decoder json => {
    open Json.Decode;
    {
      email: json |> field "email" string,
      forenames: json |> field "forenames" string,
      lastname: json |> field "lastname" string,
    }
  };

  let encoder user => {
    open Json.Encode;
    [
      ("email", string user.email),
      ("forenames", string user.forenames),
      ("lastname", string user.lastname)
    ] |> Js.Dict.fromList |> object_;
  };
};

module Session = {

  type t = {
    token: string,
    user: User.t
  };
  let encoder session => {
    open Json.Encode;
    [
      ("token", string session.token),
      ("user", User.encoder session.user)
    ] |> Js.Dict.fromList |> object_;
  };

  let decoder json => {
    open Json.Decode;
    {
      token : json|> field "token" string,
      user: json |> field "user" User.decoder
    };
  };
};

module Visitor = {
type type' =
    | NotAsked
    | Private
    | PrivateToBusiness
    | Business
    | Na
    ;

  type t = {
    id: string,
    name:string,
    mobile:string,
    position: int,
    type': type'
  };
  
  let typeEncoder (visitoryType:type') => {
    open Json.Encode;
    switch (visitoryType) {
      | NotAsked => string "NotAsked"
      | Private => string "Private"
      | PrivateToBusiness => string "PrivateToBusiness"
      | Business => string "Business"
      | Na => string "N/A"
      };
  };

  let typeDecoder json => {
    switch (Json.Decode.string json) {
    | "Private" => Private
    | "PrivateToBusiness" => PrivateToBusiness
    | "Business" => Business
    | "Na" => Na
    | a => raise @@ Json.Decode.DecodeError (a ^ "is not a valid visitor type") 
    }
  };

  
  let decoder json => {
    open Json.Decode;
    {
      id: json |> field "id" string,
      name: json |> field "name" string,
      mobile: json |> field "mobile" string,
      position: json |> field "position" int,
      type': json |> field "type" typeDecoder,
    };
  };

  let encoder visitor => {
    open Json.Encode;
    [
      ("id", string visitor.id),
      ("name", string visitor.name),
      ("mobile", string visitor.mobile),
      ("type", typeEncoder visitor.type'),
    ] |> Js.Dict.fromList |> object_;
  }

};

module VisitorForm = {

   type t = {
    type': Visitor.type',
    queue: Remote.t string string,
    name: string,
    mobile: string,
    concent: bool
  };
  let empty:t = {
    type': NotAsked,
    queue: NotAsked,
    name: "",
    mobile: "",
    concent: false
  };

  let encoder queueForm => {
    open Json.Encode;
    [
      ("type", Visitor.typeEncoder queueForm.type'),
      ("name", string queueForm.name),
      ("mobile", string queueForm.mobile)
    ] |> Js.Dict.fromList |> object_;
  };
};

module Queue = {
  type t = {
    id:string,
    name:string,
    description: string,
    order: string
  };

  let decoder json => {
    open Json.Decode;
    {
      id: json |> field "id" string,
      name: json |> field "name" string,
      description: json |> field "description" string,
      order: json |> field "order" string
    };
  };
  let encoder queue => {
    open Json.Encode;
    [
      ("id", string queue.id),
      ("name", string queue.name),
      ("description", string queue.description),
      ("order", string queue.order)
    ] |> Js.Dict.fromList |> object_;

  }
};

module Model = {
  type t = {
    session: Remote.t string Session.t,
    page: Page.t,
    loginForm: LoginForm.t,
    visitorForm: VisitorForm.t,
    visitor: Remote.t string Visitor.t,
    queues: Remote.t string (list Queue.t)
  };

  let empty: t = {
    session: NotAsked,
    page: Login,
    loginForm: LoginForm.empty, 
    visitorForm: VisitorForm.empty,
    visitor: NotAsked,
    queues: NotAsked
  };

  let encoder model => {
    open Json.Encode;

    let listEncoder encoder xs => Json.Encode.array @@ Array.of_list @@ List.map encoder xs;

    [
      ("session", Remote.encoder string Session.encoder model.session),
      ("page", Page.encoder model.page),
      ("loginForm", LoginForm.encoder model.loginForm),
      ("visitorForm", VisitorForm.encoder model.visitorForm),
      ("visitor", Remote.encoder string Visitor.encoder model.visitor),
      ("queues", Remote.encoder string (listEncoder Queue.encoder) model.queues)
    ] |> Js.Dict.fromList |> object_
  };
};
module Action = {
  type t =
    | NoOp
    | Goto Page.t
    | Reset
    | UpdateLoginForm LoginForm.t
    | Login LoginForm.t
    | LoginSuccess Session.t
    | LoginError string
    | SetVisitorType Visitor.type'
    | SetVisitorQueue string
    | UpdateVisitorForm VisitorForm.t
    | SubmitVisitorForm VisitorForm.t
    | SubmitVisitorFormError string
    | SubmitVisitorFormSuccess Visitor.t
    | FetchQueuesError string
    | FetchQueuesSuccess (list Queue.t)
  ;


  let toString action => {
    let stringify = Js.Json.stringify;
    switch action {
    | NoOp => "NoOp"
    | Reset => "Reset"
    | Goto page => "Goto " ^(page |> Page.encoder |> stringify)
    | UpdateLoginForm loginForm => "UpdateLoginForm " ^ (loginForm |> LoginForm.encoder |> stringify)
    | LoginSuccess session => "LoginSuccess " ^ (session |> Session.encoder |> stringify)
    | Login loginForm => "Login " ^ (loginForm |> LoginForm.encoder |> stringify)
    | LoginError err => "LoginError " ^ (err |> Json.Encode.string |> stringify)
    | SetVisitorType visitorType => "SelectVisitorType " ^ (visitorType |> Visitor.typeEncoder |> stringify)
    | SetVisitorQueue queue => "SelectVisitorInterests " ^ queue
    | UpdateVisitorForm visitorForm => "UpdateVisitorForm " ^ (visitorForm |> VisitorForm.encoder |> stringify)
    | SubmitVisitorForm visitorForm => "SubmitVisitorForm " ^ (visitorForm |>VisitorForm.encoder |> stringify)
    | SubmitVisitorFormError err => "SubmitQueueFormError " ^ (err |> Json.Encode.string |> stringify)
    | SubmitVisitorFormSuccess _ => "SubmitQueueFormSuccess "
    | FetchQueuesError err => "FetchQueuesError " ^ err
    | FetchQueuesSuccess _ => "FetchQueuesSuccess"
  ;
    };
  };
};