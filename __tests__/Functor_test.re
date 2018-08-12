open Jest;
open Functor;

describe("List Functor", () => {
  module ListFunctorLaws = FunctorLaws(ListFunctor);
  open ListFunctorLaws;
  open Expect;

  test("Functor Laws", () =>
    expect(idLaw([])) |> toBe(true));
    expect(idLaw([1, 2])) |> toBe(true) |> ignore;

    let f = x => x mod 2;
    let g = x => x - 1;

    expect(composeLaw(f, g, [])) |> toBe(true) |> ignore;
    expect(composeLaw(f, g, [1, 2, 3])) |> toBe(true) |> ignore;
});

describe("Option Functor", () => {
  module OptionFunctorLaws = FunctorLaws(OptionFunctor);
  open OptionFunctorLaws;
  open Expect;

  test("Functor Laws", () =>
    expect(idLaw(None)) |> toBe(true)) |> ignore;
    expect(idLaw(Some(5))) |> toBe(true) |> ignore;

    let f = x => x mod 2;
    let g = x => x - 1;

    expect(composeLaw(f, g, None)) |> toBe(true) |> ignore;
    expect(composeLaw(f, g, Some(5))) |> toBe(true) |> ignore;
});