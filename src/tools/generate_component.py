import sys
import os

def generate_component_class(name, subpath):
    # Base path : dossier "src"
    base_path = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))

    # Retirer le préfixe "src" dans subpath si présent
    if subpath.startswith("src" + os.sep):
        subpath = subpath[len("src" + os.sep):]

    target_path = os.path.join(base_path, subpath) if subpath else base_path
    os.makedirs(target_path, exist_ok=True)

    hpp_path = os.path.join(target_path, f"{name}.hpp")
    cpp_path = os.path.join(target_path, f"{name}.cpp")

    hpp_content = f"""#pragma once

#include "components/Component.hpp"

class {name} : public Component
{{
public:
    {name}();
    ~{name}() override;

    void Init(GameObject* owner) override;
    void Update() override;
    void Destroy() override;
}};
"""

    cpp_content = f"""#include "{name}.hpp"

{name}::{name}() {{}}

{name}::~{name}() {{}}

void {name}::Init(GameObject* owner)
{{
    Component::Init(owner);
    // Custom init
}}

void {name}::Update()
{{
    // Custom update
}}

void {name}::Destroy()
{{
    // Custom destroy
}}
"""

    with open(hpp_path, "w") as hpp_file:
        hpp_file.write(hpp_content)

    with open(cpp_path, "w") as cpp_file:
        cpp_file.write(cpp_content)

    print(f"✅ Fichiers générés dans {target_path}: {name}.hpp, {name}.cpp")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python generate_component.py NomClasse chemin/relatif")
    else:
        print("ARG 2")
        print(sys.argv[2])
        class_name = sys.argv[1]
        relative_path = sys.argv[2]
        generate_component_class(class_name, relative_path)
