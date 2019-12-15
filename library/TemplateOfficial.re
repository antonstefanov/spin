let path =
  Utils.Filename.concat(Config.SPIN_CACHE_DIR.get(), "spin-templates");

let branch = "template/cli";

let url = "git@github.com:tmattio/spin-templates.git";
let ensureDownloaded = () =>
  if (Utils.Filename.test(Utils.Filename.Is_dir, path)) {
    Console.log(<Pastel> "📡  Updating official templates." </Pastel>);
    let _ = Lwt_main.run(Vcs.gitPull(path));
    Console.log(
      <Pastel color=Pastel.GreenBright bold=true> "Done!\n" </Pastel>,
    );
  } else {
    Console.log(<Pastel> "📡  Downloading official templates." </Pastel>);
    let _ = Lwt_main.run(Vcs.gitClone(url, ~destination=path, ~branch));
    Console.log(
      <Pastel color=Pastel.GreenBright bold=true> "Done!\n" </Pastel>,
    );
  };

let all = (): list(ConfigFile.Doc.doc) => {
  Caml.Sys.readdir(path)
  |> Array.to_list
  |> List.filter(~f=el =>
       Caml.Sys.is_directory(Utils.Filename.concat(path, el))
     )
  |> List.filter(~f=el =>
       switch (Caml.String.get(el, 0)) {
       | '.'
       | '_' => false
       | _ => true
       }
     )
  |> List.map(~f=el =>
       ConfigFile.Doc.parse_doc(Utils.Filename.concat(path, el))
     );
};
