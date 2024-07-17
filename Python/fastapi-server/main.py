from typing import Optional
from fastapi import FastAPI
from pydantic import BaseModel

# Hardware Component Class
class HwComponent(BaseModel):
    id: int
    name: str
    description: Optional[str] = None

# Hardware Components collection
comps = {}

# FastAPI application
app = FastAPI()

@app.post("/components")
async def add_component(comp: HwComponent):
    if comp.id in comps:
        return {"ok": False, "msg": f"Component with id={comp.id} already exists"}

    comps[comp.id] = comp
    return {"ok": True, "msg": f"Component with id={comp.id} added successfully"}


@app.delete("/components/{id}")
async def del_component(id: int):
    if id not in comps:
        return {"ok": False, "msg": f"Component with id={id} doesn't exist"}

    comps.pop(id)
    return {"ok": True, "msg": f"Component with id={id} deleted successfully"}


@app.put("/component/{id}")
async def update_component(id: int, name: str, description: Optional[str] = None):
    if id not in comps:
        return {"ok": False, "msg": f"Component with id={id} doesn't exist"}

    comps[id] = HwComponent(id=id, name=name, description=description)
    return {"ok": True, "msg": f"Component with id={id} updated successfully"}


@app.get("/components")
async def get_components():
    return {"data": comps}

