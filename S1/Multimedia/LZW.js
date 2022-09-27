function encodeLZW(msg) {
  if (msg) {
    const GetOutput = (key, list) => {
      return {
        key,
        code:
          key.length === 1
            ? key.charCodeAt(0)
            : list.find((elm) => elm.key === key).code,
      };
    };
    let i = 1,
      p = msg[0],
      output = [],
      list = [];
    for (let i = 1; i < msg.length; i++) {
      const c = msg[i];
      if (list.find((elm) => elm.key === p + c)) p += c;
      else {
        output.push(GetOutput(p, list));
        list.push({ key: p + c, code: 256 + list.length });
        p = c;
      }
    }
    output.push(GetOutput(p, list));
    return { list, output };
  }
}
function decodeLZW(encode, table) {
  const translate = (code) =>
    code < 256
      ? String.fromCharCode(code)
      : table.find((elm) => elm.code == code).key;
  let list = [],
    OLD = encode[0],
    output = translate(OLD),
    C;
  for (let i = 1; i < encode.length; i++) {
    const NEW = encode[i];
    if (list.includes(NEW)) {
      S = translate(OLD);
      S += C;
    } else S = translate(NEW);
    output += S;
    C = S[0];
    list.push(OLD + C);
    OLD = NEW;
  }
  return output;
}
let { output: encode, list } = encodeLZW(prompt("Enter message to encode"));
alert(
  decodeLZW(
    encode.map((elm) => elm.code),
    list
  )
);
