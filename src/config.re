let host = {
  open ReactNative.Platform;
  switch os {
  | IOS => "http://localhost:8080"
  | Android => "http://10.0.2.2:8080"
  }
};
