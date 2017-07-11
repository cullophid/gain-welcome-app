let setItem key value =>
  Task.fromLazyPromise (fun () => ReactNative.AsyncStorage.setItem key value ());

let getItem key => Task.fromLazyPromise (fun () => ReactNative.AsyncStorage.getItem key ());
